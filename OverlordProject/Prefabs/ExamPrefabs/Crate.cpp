#include "stdafx.h"
#include "Crate.h"

#include "Materials/DiffuseMaterial.h"
#include <Prefabs/ExamPrefabs/Crash.h>
#include <Prefabs/ExamPrefabs/WumpaFruit.h>
#include <Prefabs/ExamPrefabs/OneUpPickup.h>
#include <Materials/Shadow/DiffuseMaterial_Shadow.h>
#include <Prefabs/ExamPrefabs/ParticleLifetime.h>

Crate::Crate(const XMFLOAT3& position, CrateType cratetype, int lives)
	: m_Position{position}
	, m_CrateType{cratetype}
	, m_Lives{lives}
{
	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Bounce_Crate.wav", FMOD_DEFAULT, nullptr, &m_pBounceSound);
	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Crate_Break.wav", FMOD_DEFAULT, nullptr, &m_pCrateBreakSound);
}

Crate::~Crate()
{
}

void Crate::Destoy(Crash* pCrash)
{
	if (m_CrateType == CrateType::CheckPoint_Crate)
		pCrash->SetCheckpoint(GetTransform()->GetPosition());

	m_Hit = true;
	m_Lives = 0;
}

void Crate::RenderGui()
{
	if (ImGui::CollapsingHeader("Crate"))
	{
		float position[3] = { GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, GetTransform()->GetPosition().z };
		if (ImGui::InputFloat3("Position", position))
			GetTransform()->Translate(position[0], position[1], position[2]);

	}
}

void Crate::Initialize(const SceneContext&)
{
	GetTransform()->Translate(m_Position);
	SetTag(L"Crate");

	auto bounceObject = AddChild(new GameObject());
	bounceObject->GetTransform()->Translate(m_Position.x, m_Position.y + 0.75f, m_Position.z);
	bounceObject->SetTag(L"Crate");

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

	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pModel->SetMaterial(material);
	
	material->SetDiffuseTexture(L"Textures/tex_crate.png");

	auto rigidbody = AddComponent(new RigidBodyComponent(true));
	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	rigidbody->AddCollider(PxBoxGeometry{ 0.35f, 0.35f, 0.35f }, *pDefaultMaterial, false, PxTransform{PxVec3{0.f, 0.25f, 0.f}});

	rigidbody = bounceObject->AddComponent(new RigidBodyComponent(true));
	rigidbody->AddCollider(PxBoxGeometry{ 0.35f, 0.125f , 0.35f }, *pDefaultMaterial, true);

	bounceObject->SetOnTriggerCallBack(std::bind(&Crate::OnBoxJump, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void Crate::Update(const SceneContext& /*sceneContext*/)
{
	if (m_Hit)
	{
		auto position = GetChild<GameObject>()->GetTransform()->GetPosition();

		switch (m_CrateType)
		{
		case CrateType::Defaut_Crate:
			GetScene()->AddChild((new WumpaFruit(position)));
			break;
		case CrateType::PowerUp_Crate:
			GetScene()->AddChild(new OneUpPickup(position));
			break;
		}
		m_Hit = false;
	}

	if (m_Lives <= 0)
	{
		SoundManager::Get()->GetSystem()->playSound(m_pCrateBreakSound, nullptr, false, nullptr);
		GetScene()->AddChild(new ParticleLifetime(GetTransform()->GetPosition(), 1.0f));

		GetScene()->RemoveChild(this, true);

	}
}

void Crate::OnBoxJump(GameObject* pThisObject, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Player" && action == PxTriggerAction::ENTER)
	{
		auto pCrash = static_cast<Crash*>(pOtherObject);
		pCrash->Jump(pOtherObject->GetScene()->GetSceneContext());

		if (m_CrateType == CrateType::CheckPoint_Crate)
			pCrash->SetCheckpoint(pThisObject->GetTransform()->GetPosition());

		--m_Lives;
		m_Hit = true;

		SoundManager::Get()->GetSystem()->playSound(m_pBounceSound, nullptr, false, nullptr);
	}
}
