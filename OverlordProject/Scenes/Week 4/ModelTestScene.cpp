#include "stdafx.h"
#include "ModelTestScene.h"
#include <Materials/DiffuseMaterial.h>

void ModelTestScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;
	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	auto pGameObject = AddChild(new GameObject());
	m_pColorMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();

	m_pColorMaterial->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	auto pModel = new ModelComponent(L"Models/Chair.ovm");
	pModel->SetMaterial(m_pColorMaterial);

	auto pRigidBody = new RigidBodyComponent();
	auto convexMesh = ContentManager::Load<PxConvexMesh>(L"Models/Chair.ovpc");

	pRigidBody->AddCollider(PxConvexMeshGeometry{convexMesh}, *pDefaultMaterial);

	pGameObject->AddComponent(pRigidBody);
	pGameObject->AddComponent(pModel);
	pGameObject->GetTransform()->Translate(0.f, 10.f, 0.f);

}

void ModelTestScene::Update()
{
}

void ModelTestScene::Draw()
{
}

void ModelTestScene::OnGUI()
{
	m_pColorMaterial->DrawImGui();
}
