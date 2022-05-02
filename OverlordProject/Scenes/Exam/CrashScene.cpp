#include "stdafx.h"
#include "CrashScene.h"

// Materials
#include <Materials/DiffuseMaterial.h>

// Prefabs
#include <Prefabs/ExamPrefabs/Crash.h>
#include <Prefabs/ExamPrefabs/WumpaFruit.h>
#include <Prefabs/ExamPrefabs/Crate.h>
#include <Prefabs/ExamPrefabs/PathCamera.h>
#include <Prefabs/ExamPrefabs/Crab.h>

#include <Materials/ColorMaterial.h>
#include <Materials/Shadow/DiffuseMaterial_Shadow.h>

CrashScene::~CrashScene()
{
}

void CrashScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;


	m_SceneContext.pLights->SetDirectionalLight({ -125.6139526f,66.1346436f,-41.1850471f }, { 0.740129888f, -0.597205281f, 0.309117377f });

	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Crash_Theme.wav", FMOD_LOOP_NORMAL, nullptr, &m_pTheme);
	SoundManager::Get()->GetSystem()->playSound(m_pTheme, nullptr, false, nullptr);

	//Ground Plane
	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	//GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);


	//Character
	CrashDesc characterDesc{ pDefaultMaterial, 0.25f, 1.0f };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;
	characterDesc.actionId_Attack = CharacterAttack;

	m_pCrash = AddChild(new Crash(characterDesc));
	m_pCrash->GetTransform()->Translate(0.f, 6.f, 0.f);


	m_pCamera = AddChild( 
		new PathCamera(m_pCrash->GetTransform(),
			std::vector<XMFLOAT3>{
			XMFLOAT3(0.f, 1.25f, -5.5f),
			XMFLOAT3{ 0.f, 1.25f, 10.f },
			XMFLOAT3{ 0.f, -2.5f, 25.f },
			XMFLOAT3{ 0.f, -1.75f, 37.5f },
			XMFLOAT3{ 0.f, -1.75f, 50.f },
			XMFLOAT3{ 0.f, 2.f , 65.f },
			XMFLOAT3{ 0.f, 1.25f , 100.f },
			XMFLOAT3{ 0.f, 6.f, 107.f },
			XMFLOAT3{ 0.f, 14.f, 110.f },
			XMFLOAT3{ 0.f, 14.f, 125.f }
		}, XMFLOAT3{0.f, 1.f, -2.5f}
	));

	auto cameraComponent = m_pCamera->GetComponent<CameraComponent>();
	cameraComponent->SetActive(true); //Uncomment to make this camera the active camera

	//for (int i = 0; i < 20; ++i)
	//{
	//	AddChild(new WumpaFruit(XMFLOAT3{ 0.f, .5f, 1.f + 10.f * i}));
	//}
	auto pCrate = AddChild(new Crate(XMFLOAT3{ -1.0f, 0.f, 2.0f }));

	pCrate = AddChild(new Crate(XMFLOAT3{ -1.0f, 0.f, 5.0f }));
	
	pCrate = AddChild(new Crate(XMFLOAT3{ 1.0f, 0.f, 3.5f }, Crate::CrateType::PowerUp_Crate, 1));
	pCrate = AddChild(new Crate(XMFLOAT3{ 1.0f, -3.75f, 37.f }, Crate::CrateType::CheckPoint_Crate, 1));

	AddChild(new Crab(XMFLOAT3{ 4.0f, -4.f, 27.5f }, XMFLOAT3{ -1.0f, -4.f, 27.5f }));

	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/CrashALike_32.fnt");

	GameObject* pLevel = AddChild(new GameObject());
	auto pModel = pLevel->AddComponent(new ModelComponent(L"Models/Level/Level_Detail.ovm"));


	auto pSandMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pSandMaterial->SetDiffuseTexture(L"Textures/Level_Textures/Sand.png");

	auto pBrickMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pBrickMaterial->SetDiffuseTexture(L"Textures/Level_Textures/Brick.png");

	auto pShipMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	auto pRockMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pRockMaterial->SetDiffuseTexture(L"Textures/Level_Textures/Rocks.jpeg");

	auto pTreeMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pTreeMaterial->SetDiffuseTexture(L"Textures/Level_Textures/palmTr.png");

	auto pLeaveMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pLeaveMaterial->SetDiffuseTexture(L"Textures/Level_Textures/PalmsTreesTexture.png");

	auto pPillarMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pPillarMaterial->SetDiffuseTexture(L"Textures/Level_Textures/Pillar_color.png");

	auto pTempleMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pTempleMaterial->SetDiffuseTexture(L"Textures/Level_Textures/Temple_Texture.png");

	pModel->SetMaterial(pSandMaterial, 0);
	pModel->SetMaterial(pBrickMaterial, 1);
	pModel->SetMaterial(pShipMaterial, 2);
	pModel->SetMaterial(pRockMaterial, 3);
	//pModel->SetMaterial(pRockMaterial, 3);
	pModel->SetMaterial(pTreeMaterial, 4);
	pModel->SetMaterial(pLeaveMaterial, 5);
	pModel->SetMaterial(pPillarMaterial, 7);
	//pModel->SetMaterial(pTempleMaterial, 8);

	auto pRigidbody = new RigidBodyComponent(true);
	auto triangleMesh = ContentManager::Load<PxTriangleMesh>(L"Models/Level/Level_Collision.ovpt");
	pRigidbody->AddCollider(PxTriangleMeshGeometry{ triangleMesh }, *pDefaultMaterial, false);
	pLevel->AddComponent(pRigidbody);

	pLevel->GetTransform()->Rotate(90.f, 0.f, 0.0f);

	auto pKillTrigger = AddChild(new GameObject());
	pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
	pRigidbody->AddCollider(PxBoxGeometry{ 100.f, .5f, 100.f }, *pDefaultMaterial, true);

	pKillTrigger->GetTransform()->Translate(0, -7.5f, 0.f);

	pKillTrigger->SetOnTriggerCallBack(std::bind(&CrashScene::Killzone, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//Input
	auto inputAction = InputAction(CharacterMoveLeft, InputState::down, 'A');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveRight, InputState::down, 'D');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveForward, InputState::down, 'W');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveBackward, InputState::down, 'S');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterJump, InputState::pressed, VK_SPACE, -1, XINPUT_GAMEPAD_A);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterAttack, InputState::pressed, 'Q');
	m_SceneContext.pInput->AddInputAction(inputAction);
}

void CrashScene::Update()
{
}

void CrashScene::OnGUI()
{
	m_pCrash->DrawImGui();
	m_pCamera->DrawImGui();
}

void CrashScene::Killzone(GameObject*, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Player" && action == PxTriggerAction::ENTER)
	{
		m_pCrash->PlayerDeath();
	}
}
