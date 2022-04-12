#include "stdafx.h"
#include "Crate.h"

#include "Materials/DiffuseMaterial.h"
#include <Prefabs/ExamPrefabs/Crash.h>
#include <Prefabs/ExamPrefabs/WumpaFruit.h>

Crate::Crate(const XMFLOAT3& position, CrateType cratetype)
	: m_Position{position}
	, m_CrateType{cratetype}
{
}

void Crate::Initialize(const SceneContext&)
{
	GetTransform()->Translate(m_Position);

	switch (m_CrateType)
	{
	case CrateType::Defaut_Crate:

		break;
	}

	ModelComponent* pModel;
	switch (m_CrateType)
	{
	case	CrateType::PowerUp_Crate:
		pModel = AddComponent(new ModelComponent(L"Models/Crate_OneUp.ovm"));
		break;
	default:
		pModel = AddComponent(new ModelComponent(L"Models/crate.ovm"));
		break;
	}

	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pModel->SetMaterial(material);
	
	material->SetDiffuseTexture(L"Textures/tex_crate.png");

	auto rigidbody = AddComponent(new RigidBodyComponent(true));

	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	rigidbody->AddCollider(PxBoxGeometry{ 0.25f, 0.25f, 0.25f }, *pDefaultMaterial, false, PxTransform{PxVec3{0.f, 0.25f, 0.f}});

	auto bounceObject = AddChild( new GameObject());
	bounceObject->GetTransform()->Translate(m_Position.x, m_Position.y + 0.75f,m_Position.z );
	
	rigidbody = bounceObject->AddComponent(new RigidBodyComponent(true));
	rigidbody->AddCollider(PxBoxGeometry{ 0.3f, 0.125f , 0.3f }, *pDefaultMaterial, true);

	bounceObject->SetOnTriggerCallBack(std::bind(&Crate::OnBoxJump, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

}

void Crate::Update(const SceneContext& /*sceneContext*/)
{
	if (m_Hit)
	{
		auto position = GetChild<GameObject>()->GetTransform()->GetPosition();
		SceneManager::Get()->GetActiveScene()->AddChild(new WumpaFruit(position));
		m_Hit = false;
	}

	if (m_Lives <= 0)
	{
		SceneManager::Get()->GetActiveScene()->RemoveChild(this, true);
	}
}

void Crate::OnBoxJump(GameObject* /*pThisObject*/, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Player" && action == PxTriggerAction::ENTER)
	{
		auto pCrash = static_cast<Crash*>(pOtherObject);
		pCrash->Jump(pOtherObject->GetScene()->GetSceneContext());
		--m_Lives;
		m_Hit = true;
	}
}
