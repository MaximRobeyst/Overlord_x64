#include "stdafx.h"
#include "UberMaterialScene.h"
#include <Materials/UberMaterial.h>

void UberMaterialScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	auto pGameObject = AddChild(new GameObject());
	m_pUberMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();

	auto pModel = new ModelComponent(L"Models/Sphere.ovm");
	pModel->SetMaterial(m_pUberMaterial);

	pGameObject->AddComponent(pModel);
	pGameObject->GetTransform()->Scale(10.f);

	GetSceneSettings().drawGrid = false;
}

void UberMaterialScene::Update()
{
}

void UberMaterialScene::Draw()
{
}

void UberMaterialScene::OnGUI()
{
	m_pUberMaterial->DrawImGui();
}
