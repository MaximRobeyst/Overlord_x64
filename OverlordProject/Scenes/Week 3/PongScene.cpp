#include "stdafx.h"
#include "PongScene.h"
#include "Prefabs/CubePrefab.h"
#include "Prefabs//SpherePrefab.h"

void PongScene::Initialize()
{
	m_pPeddle1 = AddChild(new CubePrefab(0.75f, 2.f, 0.75f, XMFLOAT4{Colors::White}));
	m_pPeddle1->GetTransform()->Translate(-5.f, 0.f, 0.f);
	m_pPeddle2 = AddChild(new CubePrefab{ 0.75f, 2.f, 0.75f, XMFLOAT4{Colors::White} });
	m_pPeddle2->GetTransform()->Translate(5, 0.f, 0.f);

	//auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	m_pBall = AddChild(new SpherePrefab(.25f, 10, XMFLOAT4{ Colors::Red }));
	
	GameObject* pCameraObject = AddChild(new GameObject());
	CameraComponent* pCamera = new CameraComponent();
	pCameraObject->AddComponent(pCamera);
	SetActiveCamera(pCamera);

	GetSceneSettings().clearColor = XMFLOAT4{ Colors::Black };
	GetSceneSettings().drawGrid = false;

	pCameraObject->GetTransform()->Translate(0.f, 0.f, -9.f);
}

void PongScene::Update()
{
}

void PongScene::Draw()
{
}

void PongScene::OnGUI()
{
}
