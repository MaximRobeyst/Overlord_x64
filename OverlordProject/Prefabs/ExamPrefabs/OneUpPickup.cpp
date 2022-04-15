#include "stdafx.h"
#include "OneUpPickup.h"
#include <Materials/DiffuseMaterial.h>
#include <Prefabs/ExamPrefabs/Crash.h>

OneUpPickup::OneUpPickup(XMFLOAT3 position)
	: m_Position{position}
{
	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Extra_Life.wav", FMOD_DEFAULT, nullptr, &m_pSound);
}

void OneUpPickup::Initialize(const SceneContext&)
{
	auto model = AddComponent(new ModelComponent(L"Models/wumpaFruit.ovm"));
	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	model->SetMaterial(material);

	material->SetDiffuseTexture(L"Textures/tex_wumpafruit.png");
	GetTransform()->Scale(2.f);
	GetTransform()->Translate(m_Position);

	auto rigidBody = new RigidBodyComponent(true);

	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	rigidBody->AddCollider(PxSphereGeometry{ 0.25f }, *pDefaultMaterial, true);

	AddComponent(rigidBody);

	SetOnTriggerCallBack(std::bind(&OneUpPickup::CollectLife, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void OneUpPickup::Update(const SceneContext& sceneContext)
{
	GetTransform()->Rotate(0.f, 45.f * sceneContext.pGameTime->GetTotal(), 0.f);

	if (deleteObject)
		SceneManager::Get()->GetActiveScene()->RemoveChild(this, true);
}

void OneUpPickup::CollectLife(GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Player" && action == PxTriggerAction::ENTER)
	{
		auto crash = static_cast<Crash*>(pOtherObject);
		crash->AddLife();
		deleteObject = true;

		SoundManager::Get()->GetSystem()->playSound(m_pSound, nullptr, false, nullptr);
	}
}
