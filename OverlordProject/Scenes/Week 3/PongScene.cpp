#include "stdafx.h"
#include "PongScene.h"
#include "Prefabs/CubePrefab.h"
#include "Prefabs//SpherePrefab.h"

void PongScene::Initialize()
{
	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	auto rigidBody = new RigidBodyComponent(true);
	m_pPeddle1 = AddChild(new CubePrefab(0.75f, 2.f, 0.75f, XMFLOAT4{ Colors::White }));
	m_pPeddle1->GetTransform()->Translate(-5.f, 0.f, 0.f);
	m_pPeddle1->AddComponent(rigidBody);
	auto colliderId = rigidBody->AddCollider(PxBoxGeometry{ 0.75f / 2.f, 1.f, 0.75f / 2.f }, *pDefaultMaterial, true);
	rigidBody->GetCollider(colliderId).SetTrigger(true);

	rigidBody = new RigidBodyComponent(true);
	rigidBody->AddCollider(PxBoxGeometry{ 0.75f / 2.f, 1.f, 0.75f / 2.f }, *pDefaultMaterial, true);

	m_pPeddle2 = AddChild(new CubePrefab{ 0.75f, 2.f, 0.75f, XMFLOAT4{Colors::White} });
	m_pPeddle2->GetTransform()->Translate(5, 0.f, 0.f);
	m_pPeddle2->AddComponent(rigidBody);

	rigidBody = new RigidBodyComponent(true);
	m_pTopBoundary = AddChild(new GameObject());
	m_pTopBoundary->AddComponent(rigidBody);
	m_pTopBoundary->GetTransform()->Translate(0.f, 4.0f, 0.f);
	colliderId = rigidBody->AddCollider(PxBoxGeometry{ 7.5f , 0.375f, 0.375f }, *pDefaultMaterial, true);
	rigidBody->GetCollider(colliderId).SetTrigger(true);

	rigidBody = new RigidBodyComponent(true);
	rigidBody->AddCollider(PxBoxGeometry{ 7.5f , 0.375f, 0.375f }, *pDefaultMaterial, true);
	m_pBottomBoundary = AddChild(new GameObject());
	m_pBottomBoundary->AddComponent(rigidBody);
	m_pBottomBoundary->GetTransform()->Translate(0.f, -4.f, 0.f);

	//auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	m_pBall = AddChild(new SpherePrefab(.25f, 10, XMFLOAT4{ Colors::Red }));

	rigidBody = new RigidBodyComponent();
	m_pBall->AddComponent(rigidBody);
	rigidBody->AddCollider(PxSphereGeometry{ .25f },*pDefaultMaterial);
	rigidBody->SetKinematic(true);

	rigidBody = new RigidBodyComponent(true);
	rigidBody->AddCollider(PxBoxGeometry{ 0.375f , 7.5f, 0.375f }, *pDefaultMaterial, true);
	auto gameobject = AddChild(new GameObject());
	gameobject->AddComponent(rigidBody);
	gameobject->GetTransform()->Translate(7.f, 0.f, 0.f);

	gameobject->SetOnTriggerCallBack(std::bind(&PongScene::Score, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	rigidBody = new RigidBodyComponent(true);
	rigidBody->AddCollider(PxBoxGeometry{ 0.375f , 7.5f, 0.375f }, *pDefaultMaterial, true);
	gameobject = AddChild(new GameObject());
	gameobject->AddComponent(rigidBody);
	gameobject->GetTransform()->Translate(-7.f, 0.f, 0.f);

	gameobject->SetOnTriggerCallBack(std::bind(&PongScene::Score, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	m_pBallVelocity = XMFLOAT3{ 1.f, 1.f, 0.f };

	m_pTopBoundary->SetOnTriggerCallBack(std::bind(&PongScene::VerticalHit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_pBottomBoundary->SetOnTriggerCallBack(std::bind(&PongScene::VerticalHit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	//m_pBall->SetOnTriggerCallBack(std::bind(&PongScene::VerticalHit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	m_pPeddle1->SetOnTriggerCallBack(std::bind(&PongScene::HorizontalHit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_pPeddle2->SetOnTriggerCallBack(std::bind(&PongScene::HorizontalHit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	
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
	DirectX::XMFLOAT3 input{};
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, 0x57))
		input.y += 1 * GetSceneContext().pGameTime->GetElapsed();
	if(GetSceneContext().pInput->IsKeyboardKey(InputState::down, 0x53))
		input.y -= 1 * GetSceneContext().pGameTime->GetElapsed();;

	XMFLOAT3 oldpos = m_pPeddle1->GetTransform()->GetPosition();
	m_pPeddle1->GetTransform()->Translate(oldpos.x + input.x, oldpos.y + input.y, oldpos.z + oldpos.z);

	input = XMFLOAT3{};
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_UP))
		input.y += 1 * GetSceneContext().pGameTime->GetElapsed();
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_DOWN))
		input.y -= 1 * GetSceneContext().pGameTime->GetElapsed();;

	oldpos = m_pPeddle2->GetTransform()->GetPosition();
	m_pPeddle2->GetTransform()->Translate(oldpos.x + input.x, oldpos.y + input.y, oldpos.z + oldpos.z);
	
	oldpos = m_pBall->GetTransform()->GetPosition();
	m_pBall->GetTransform()->Translate(
		oldpos.x + m_pBallVelocity.x * GetSceneContext().pGameTime->GetElapsed(),
		oldpos.y + m_pBallVelocity.y * GetSceneContext().pGameTime->GetElapsed(),
		oldpos.z + m_pBallVelocity.z * GetSceneContext().pGameTime->GetElapsed()
	);

}

void PongScene::Draw()
{
}

void PongScene::OnGUI()
{
}

void PongScene::Resart()
{
	m_pPeddle1->GetTransform()->Translate(-5.f, 0.f, 0.f);
	m_pPeddle2->GetTransform()->Translate(5, 0.f, 0.f);

	m_pBallVelocity = XMFLOAT3{ 1.f, 1.f, 0.f };

	m_pBall->GetTransform()->Translate(0.f, 0.f, 0.f);

	//Initialize();
}

void PongScene::VerticalHit(GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject != m_pBall)
		return;

	if (action == PxTriggerAction::ENTER)
	{
		m_pBallVelocity.y *= -1.f;
	}
}

void PongScene::HorizontalHit(GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject != m_pBall)
		return;

	if (action == PxTriggerAction::ENTER)
	{
		m_pBallVelocity.x = -1.f;
	}
}

void PongScene::Score(GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction action)
{

	if (pOtherObject != m_pBall)
		return;

	if (action == PxTriggerAction::ENTER)
	{
		Resart();
	}
}
