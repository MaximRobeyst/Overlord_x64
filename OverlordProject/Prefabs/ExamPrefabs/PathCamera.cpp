#include "stdafx.h"
#include "PathCamera.h"

#include <fstream>

PathCamera::PathCamera(TransformComponent* pFollowTarget, const XMFLOAT3& offset)
	: m_pFollowTarget{pFollowTarget}
	, m_Offset{offset}
{
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);

	auto stream = std::ifstream("Resources/camerapath.bin");
	size_t size;
	stream.read((char*)&size, sizeof(size_t));
	m_Path.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		stream.read((char*)&m_Path[i].point, sizeof(XMFLOAT3));
		stream.read((char*)&m_Path[i].rotation, sizeof(XMFLOAT3));
	}

	GetTransform()->Translate(m_Path[0].point);
}

PathCamera::~PathCamera()
{
	if (!m_Save) return;

	auto stream = std::ofstream("Resources/camerapath.bin");
	size_t size = m_Path.size();

	stream.write((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; ++i)
	{
		XMFLOAT3 rotation{};
		stream.write((char*)&m_Path[i].point, sizeof(XMFLOAT3));
		stream.write((char*)&m_Path[i].rotation, sizeof(XMFLOAT3));
	}

	stream.close();
}

void PathCamera::DrawImGui()
{
	if (ImGui::CollapsingHeader("Path Camera"))
	{
		ImGui::Checkbox("Save path", &m_Save);

		bool active = m_pCamera->IsActive();
		if (ImGui::Checkbox("Camera Active", &active))
		{
			m_pCamera->SetActive(active);
		}
		float offset[3]{ m_Offset.x, m_Offset.y, m_Offset.z };
		if (ImGui::DragFloat3("offset", offset))
		{
			m_Offset.x = offset[0];
			m_Offset.y = offset[1];
			m_Offset.z = offset[2];
		}

		ImGui::Text("Path");
		ImGui::Text( ("Current point " + std::to_string(m_CurrentIndex)).c_str() );
		for (int i = 0; i < m_Path.size(); ++i)
		{
			float point[3] = { m_Path[i].point.x, m_Path[i].point.y, m_Path[i].point.z };
			if (ImGui::InputFloat3(("Path position " + std::to_string(i)).c_str(), point))
			{
				m_Path[i].point = XMFLOAT3{ point[0], point[1] , point[2] };
			}
			float rotation[3] = { m_Path[i].rotation.x, m_Path[i].rotation.y, m_Path[i].rotation.z };
			if (ImGui::InputFloat3(("Path rotation " + std::to_string(i)).c_str(), rotation))
			{
				m_Path[i].rotation = XMFLOAT3{ rotation[0], rotation[1] , rotation[2] };
			}
			if (ImGui::Button("InsertAfter"))
			{
				m_Path.insert(m_Path.begin() + i, m_Path[i]);
			}

			ImGui::Spacing();
		}

		if (ImGui::Button("Add Button", ImVec2{ 100.0f, 20.0f }))
		{
			m_Path.push_back(PathPoint{ m_Path[m_Path.size() - 1] });
		}
		if (ImGui::Button("Remove Point", ImVec2{ 100.0f, 20.0f }))
		{
			m_Path.pop_back();
		}
	}


}

void PathCamera::ResetCamera()
{
	m_CurrentIndex = 1;
}

void PathCamera::Initialize(const SceneContext& /*sceneContext*/)
{
}

void PathCamera::Update(const SceneContext& /*sceneContext*/)
{
	// Proaby best to set a point when a checkpoint is set

	XMFLOAT3 followTargetPosition = m_pFollowTarget->GetPosition();
	followTargetPosition.y = GetTransform()->GetPosition().y;
	followTargetPosition.x = GetTransform()->GetPosition().x;

	XMVECTOR targetPosition = XMLoadFloat3(&followTargetPosition);
	XMVECTOR offset = XMLoadFloat3(&m_Offset);
	XMVECTOR v1 = XMLoadFloat3(&m_Path[m_CurrentIndex - 1].point);
	XMVECTOR v2 = XMLoadFloat3(&m_Path[m_CurrentIndex].point);
	
	targetPosition = targetPosition + offset;
	
	float length{};
	float distancePlayer{};
	float percentage{};
	float dot{};
	XMStoreFloat(&length, XMVector3LengthSq(v2 - v1));
	XMStoreFloat(&distancePlayer, XMVector3LengthSq(v1 - targetPosition));
	XMStoreFloat(&dot, XMVector3Dot(targetPosition - v1, v2 - v1));
	
	auto up = XMLoadFloat3(&GetTransform()->GetUp());


	percentage = distancePlayer / length;
	auto newPosition = XMVectorLerp(v1, v2, percentage);

	GetTransform()->Rotate(m_Path[m_CurrentIndex].rotation);

	if (percentage >= 1.0f)
		++m_CurrentIndex %= m_Path.size();
	else if (dot <= -1.f)
		--m_CurrentIndex;
	
	GetTransform()->Translate(newPosition);

	//XMFLOAT3 currenEulerRotation = MathHelper::QuaternionToEuler(GetTransform()->GetRotation());
	//auto rotation1 = XMLoadFloat3(&currenEulerRotation);
	//auto rotation2 = XMLoadFloat3(&m_Path[m_CurrentIndex].rotation);
	//
	//auto currentRotation = XMVectorLerp(rotation1, rotation2, sceneContext.pGameTime->GetElapsed());
	//
	//XMFLOAT3 finalRotation;
	//XMStoreFloat3(&finalRotation, currentRotation);
	//GetTransform()->Rotate(finalRotation);

	//GetTransform()->Rotate(XMQuaternionRotationMatrix(XMMatrixLookAtLH(newPosition, v2, up)), true);
	
	
	MathHelper::Clamp<int>(m_CurrentIndex, (int)m_Path.size() - 1, 1);

	auto target = XMVectorLerp(v1, v2, m_Percentage);
}

void PathCamera::Draw(const SceneContext& /*sceneContext*/)
{
	for (int i = 1; i < m_Path.size(); ++i)
	{
		DebugRenderer::DrawLine(m_Path[i - 1].point, m_Path[i].point, XMFLOAT4{ Colors::Red });
	}
}
