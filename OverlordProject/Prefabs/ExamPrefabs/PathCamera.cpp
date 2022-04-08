#include "stdafx.h"
#include "PathCamera.h"

PathCamera::PathCamera(TransformComponent* pFollowTarget, const std::vector<XMFLOAT3>& path)
	: m_pFollowTarget{pFollowTarget}
	, m_Path{path}
{
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);

	GetTransform()->Translate(path[0]);
}

void PathCamera::Initialize(const SceneContext& /*sceneContext*/)
{
}

void PathCamera::Update(const SceneContext& sceneContext)
{
	XMVECTOR v1 = XMLoadFloat3(&GetTransform()->GetPosition());
	XMVECTOR v2 = XMLoadFloat3(&m_Path[m_CurrentIndex]);

	auto target = XMVectorLerp(v1, v2, sceneContext.pGameTime->GetElapsed());

	float length;
	XMStoreFloat(&length, XMVector2LengthSq(v2 - target));

	GetTransform()->Translate(target);

	if (length < 0.2f * 0.2f)
		++m_CurrentIndex;

	MathHelper::Clamp<int>(m_CurrentIndex, (int)m_Path.size() - 1, 0);
}

void PathCamera::Draw(const SceneContext& /*sceneContext*/)
{
	for (int i = 1; i < m_Path.size(); ++i)
	{
		DebugRenderer::DrawLine(m_Path[i - 1], m_Path[i], XMFLOAT4{ Colors::Red });
	}
}
