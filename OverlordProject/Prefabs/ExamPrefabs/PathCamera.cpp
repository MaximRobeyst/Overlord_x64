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
		stream.read((char*)&m_Path[i], sizeof(XMFLOAT3));
	}

	GetTransform()->Translate(m_Path[0]);
}

PathCamera::~PathCamera()
{
	auto stream = std::ofstream("Resources/camerapath.bin");
	size_t size = m_Path.size();

	stream.write((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; ++i)
	{
		stream.write((char*)&m_Path[i], sizeof(XMFLOAT3));
	}

	stream.close();
}

void PathCamera::DrawImGui()
{
	if (ImGui::CollapsingHeader("Path Camera"))
	{
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
			float point[3] = { m_Path[i].x, m_Path[i].y, m_Path[i].z };
			if (ImGui::InputFloat3(("Path " + std::to_string(i)).c_str(), point))
			{
				m_Path[i] = XMFLOAT3{ point[0], point[1] , point[2] };
			}
		}

		if (ImGui::Button("Add Button", ImVec2{ 100.0f, 20.0f }))
		{
			m_Path.push_back(XMFLOAT3{ m_Path[m_Path.size() - 1] });
		}
		if (ImGui::Button("Remove Point", ImVec2{ 100.0f, 20.0f }))
		{
			m_Path.pop_back();
		}
	}


}

void PathCamera::Initialize(const SceneContext& /*sceneContext*/)
{
}

void PathCamera::Update(const SceneContext& /*sceneContext*/)
{
	XMVECTOR targetPosition = XMLoadFloat3(&m_pFollowTarget->GetPosition());
	XMVECTOR offset = XMLoadFloat3(&m_Offset);
	XMVECTOR v1 = XMLoadFloat3(&m_Path[m_CurrentIndex - 1]);
	XMVECTOR v2 = XMLoadFloat3(&m_Path[m_CurrentIndex]);
	
	targetPosition = targetPosition + offset;
	
	float length{};
	float distancePlayer{};
	float percentage{};
	float dot{};
	XMStoreFloat(&length, XMVector3LengthSq(v2 - v1));
	XMStoreFloat(&distancePlayer, XMVector3LengthSq(v1 - targetPosition));
	XMStoreFloat(&dot, XMVector3Dot(targetPosition - v1, v2 - v1));


	percentage = distancePlayer / length;
	auto newPosition = XMVectorLerp(v1, v2, percentage);

	//const XMVECTOR upVec = XMLoadFloat3(&GetTransform()->GetUp());
	//auto lookatMatrix = XMMatrixLookAtRH(newPosition, v2, upVec);
	//auto rotation  = XMQuaternionRotationMatrix(lookatMatrix);
	//GetTransform()->Rotate(rotation, true);

	if (percentage >= 1.0f)
		++m_CurrentIndex %= m_Path.size();
	else if (dot <= -1.f)
		--m_CurrentIndex;
	
	GetTransform()->Translate(newPosition);
	
	
	MathHelper::Clamp<int>(m_CurrentIndex, (int)m_Path.size() - 1, 1);

	auto target = XMVectorLerp(v1, v2, m_Percentage);
}

void PathCamera::Draw(const SceneContext& /*sceneContext*/)
{
	for (int i = 1; i < m_Path.size(); ++i)
	{
		DebugRenderer::DrawLine(m_Path[i - 1], m_Path[i], XMFLOAT4{ Colors::Red });
	}
}
