#include "stdafx.h"
#include "Crab.h"
#include <Materials/DiffuseMaterial.h>
#include <Prefabs/ExamPrefabs/Crash.h>

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

	auto rigidbody = AddComponent(new RigidBodyComponent());
	rigidbody->SetKinematic(true);
	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	rigidbody->AddCollider(PxSphereGeometry{0.5f}, *pDefaultMaterial, true, PxTransform{ PxVec3{0.f, 0.25f, 0.f} });

	SetOnTriggerCallBack(std::bind(&Crab::KillPlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

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

void Crab::KillPlayer(GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Player" && action == PxTriggerAction::ENTER)
	{
		auto crash = static_cast<Crash*>(pOtherObject);
		crash->PlayerDeath();
	}
}
