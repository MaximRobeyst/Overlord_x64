#include "stdafx.h"
#include "UberMaterialScene.h"
#include <Materials/UberMaterial.h>

void UberMaterialScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	auto pGameObject = AddChild(new GameObject());
	m_pUberMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();
	m_pTransform = pGameObject->GetTransform();

	auto pModel = new ModelComponent(L"Models/Sphere.ovm");
	pModel->SetMaterial(m_pUberMaterial);

	pGameObject->AddComponent(pModel);
	pGameObject->GetTransform()->Scale(10.f);

	GetSceneSettings().drawGrid = false;
}

void UberMaterialScene::Update()
{
	m_pTransform->Rotate(XMFLOAT3{ 0.f, m_Angle, 0.0f }, true);
	m_Angle += GetSceneContext().pGameTime->GetElapsed() * m_Speed;
	if (m_Angle >= 360.f)
		m_Angle -= 360.f;
}

void UberMaterialScene::Draw()
{
}

void UberMaterialScene::OnGUI()
{
	m_pUberMaterial->DrawImGui();
}
