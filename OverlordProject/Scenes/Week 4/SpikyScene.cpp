#include "stdafx.h"
#include "SpikyScene.h"
#include <Materials/SpikeMaterial.h>

void SpikyScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	auto pGameObject = AddChild(new GameObject());
	m_pSpikeMaterial = MaterialManager::Get()->CreateMaterial<SpikeMaterial>();
	m_pTransform = pGameObject->GetTransform();

	auto pModel = new ModelComponent(L"Models/OctaSphere.ovm");
	pModel->SetMaterial(m_pSpikeMaterial);

	pGameObject->AddComponent(pModel);
	pGameObject->GetTransform()->Scale(10.f);

	GetSceneSettings().drawGrid = false;
}

void SpikyScene::Update()
{
	m_pTransform->Rotate(XMFLOAT3{ 0.f, m_Angle, 0.0f }, true);
	m_Angle += GetSceneContext().pGameTime->GetElapsed() * m_Speed;
	if (m_Angle >= 360.f)
		m_Angle -= 360.f;
}

void SpikyScene::Draw()
{
}

void SpikyScene::OnGUI()
{
	m_pSpikeMaterial->DrawImGui();
}
