#include "stdafx.h"
#include "Crab.h"
#include <Materials/DiffuseMaterial.h>

Crab::Crab(const XMFLOAT3& position1, const XMFLOAT3& position2)
	: m_Targets{position1, position2}
{
}

void Crab::Initialize(const SceneContext& /*sceneContext*/)
{
	SetTag(L"Enemy");

	GetTransform()->Translate(m_Targets[m_CurrentIndex]);

	auto pModel = AddComponent(new ModelComponent(L"Models/Crab.ovm"));

	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pModel->SetMaterial(material);

	material->SetDiffuseTexture(L"Textures/crab_c.png");
}

void Crab::Update(const SceneContext& sceneContext)
{

	auto currentPos = XMLoadFloat3(&GetTransform()->GetPosition());
	auto targetPos = XMLoadFloat3(&m_Targets[m_CurrentIndex]);

	float distance{};
	XMStoreFloat(&distance, (XMVector3Length(currentPos - targetPos)));
	if (distance < 0.05f)
		++m_CurrentIndex %= m_Targets.size();

	currentPos = XMVectorLerp(currentPos, targetPos, sceneContext.pGameTime->GetElapsed() * m_Speed);
	GetTransform()->Translate(currentPos);
}

void Crab::Draw(const SceneContext&)
{
	DebugRenderer::DrawLine(m_Targets[0], m_Targets[1], XMFLOAT4{Colors::Red});
}
