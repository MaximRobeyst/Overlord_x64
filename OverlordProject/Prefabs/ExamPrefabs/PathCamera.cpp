#include "stdafx.h"
#include "PathCamera.h"

PathCamera::PathCamera(TransformComponent* pFollowTarget, const std::vector<XMFLOAT3>& path, const XMFLOAT3& offset)
	: m_pFollowTarget{pFollowTarget}
	, m_Path{path}
	, m_Offset{offset}
{
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);

	GetTransform()->Translate(path[0]);
}

void PathCamera::DrawImGui()
{
	bool active = m_pCamera->IsActive();
	if (ImGui::Checkbox("Camera Active", &active))
	{
		m_pCamera->SetActive(active);
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
	XMStoreFloat(&length, XMVector3LengthSq(v2 - v1));
	XMStoreFloat(&distancePlayer, XMVector3LengthSq(v1 - targetPosition));

	percentage = distancePlayer / length;
	auto newPosition = XMVectorLerp(v1, v2, percentage);

	if (percentage >= 1.0f)
		++m_CurrentIndex %= m_Path.size();
	else if (percentage <= 0.0001f)
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
