#include "stdafx.h"
#include "SpikyScene.h"
#include <Materials/SpikeMaterial.h>

void SpikyScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	auto pGameObject = AddChild(new GameObject());
	m_pSpikeMaterial = MaterialManager::Get()->CreateMaterial<SpikeMaterial>();

	auto pModel = new ModelComponent(L"Models/OctaSphere.ovm");
	pModel->SetMaterial(m_pSpikeMaterial);

	pGameObject->AddComponent(pModel);
	pGameObject->GetTransform()->Scale(10.f);

	GetSceneSettings().drawGrid = false;
}

void SpikyScene::Update()
{
}

void SpikyScene::Draw()
{
}

void SpikyScene::OnGUI()
{
	m_pSpikeMaterial->DrawImGui();
}
