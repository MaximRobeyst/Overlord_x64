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


	m_SceneContext.pLights->SetDirectionalLight({ -96.f,66.1346436f,-41.1850471f }, { 0.740129888f, -0.597205281f, 0.309117377f });
	GameObject* pLightViz = new GameObject();
	auto crateModel = pLightViz->AddComponent(new ModelComponent(L"Models/crate.ovm"));
	auto material = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	crateModel->SetMaterial(material);
	pLightViz->GetTransform()->Translate(-96.f, 66.1346436f, -41.1850471f);
	AddChild(pLightViz);

	//SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Crash_Theme.wav", FMOD_LOOP_NORMAL, nullptr, &m_pTheme);
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
		new PathCamera(m_pCrash->GetTransform(), XMFLOAT3{0.f, 1.f, -2.5f}));

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
	pRockMaterial->SetDiffuseTexture(L"Textures/Level_Textures/Rocks.png");

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
	pModel->SetMaterial(pRockMaterial, 4);
	pModel->SetMaterial(pLeaveMaterial, 5);
	pModel->SetMaterial(pTreeMaterial, 6);
	pModel->SetMaterial(pPillarMaterial, 7);
	//pModel->SetMaterial(pTempleMaterial, 8);

	auto pRigidbody = new RigidBodyComponent(true);
	auto triangleMesh = ContentManager::Load<PxTriangleMesh>(L"Models/Level/Level_Collision.ovpt");
	pRigidbody->AddCollider(PxTriangleMeshGeometry{ triangleMesh }, *pDefaultMaterial, false);
	pLevel->AddComponent(pRigidbody);

	pLevel->GetTransform()->Rotate(90.f, 0.f, 0.0f);

	auto pKillTrigger = AddChild(new GameObject());
	pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
	pRigidbody->AddCollider(PxBoxGeometry{ 1000.f, .5f, 1000.f }, *pDefaultMaterial, true);

	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.0f, 2.0f, 100.0f }, Crate::CrateType::Jump_Crate, -1));
	AddChild(m_pCrates.back());
	

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
	m_SceneContext.pLights->GetDirectionalLight().position.z = -41.1850471f + m_pCrash->GetTransform()->GetPosition().z;
}

void CrashScene::PostDraw()
{
	//Draw ShadowMap (Debug Visualization)
	//if (m_DrawShadowMap) {
	//
	//	ShadowMapRenderer::Get()->Debug_DrawDepthSRV({ m_SceneContext.windowWidth - (720.f * m_ShadowMapScale), 10.f }, { m_ShadowMapScale, m_ShadowMapScale }, { 0.f,0.f });
	//}
}

void CrashScene::OnGUI()
{
	ImGui::Checkbox("Draw ShadowMap", &m_DrawShadowMap);
	float position[3]{ m_SceneContext.pLights->GetDirectionalLight().position.x, m_SceneContext.pLights->GetDirectionalLight().position.y, m_SceneContext.pLights->GetDirectionalLight().position.z };
	if (ImGui::InputFloat3("Camera position: ", position))
	{
		XMFLOAT4 directionalLightPosition{ position[0], position[1], position[2], m_SceneContext.pLights->GetDirectionalLight().position.w };
		m_SceneContext.pLights->GetDirectionalLight().position = directionalLightPosition;
	}

	//float direction[3]{ m_SceneContext.pLights->GetDirectionalLight().direction.x, m_SceneContext.pLights->GetDirectionalLight().direction.y, m_SceneContext.pLights->GetDirectionalLight().direction.z };
	//if (ImGui::InputFloat3("Camera position: ", direction, "%.3f", 1))
	//{
	//	XMFLOAT4 directionalLightPosition{ direction[0], direction[1], direction[2], m_SceneContext.pLights->GetDirectionalLight().direction.w };
	//	m_SceneContext.pLights->GetDirectionalLight().position = directionalLightPosition;
	//}

	m_pCrash->DrawImGui();
	m_pCamera->DrawImGui();

	if (ImGui::CollapsingHeader("Crates"))
	{
		for (auto crate : m_pCrates)
		{
			float cratePosition[3] = { crate->GetTransform()->GetPosition().x, crate->GetTransform()->GetPosition().y, crate->GetTransform()->GetPosition().z};
			
			if (ImGui::InputFloat3("Crate position", cratePosition))
			{
				crate->GetTransform()->Translate(cratePosition[0], cratePosition[1], cratePosition[2]);
			}
		}
	}

	
	XMFLOAT3 lightPosition;
	XMStoreFloat3(&lightPosition, XMLoadFloat4(&m_SceneContext.pLights->GetDirectionalLight().position));
	XMFLOAT3 targetPosition;
	XMStoreFloat3(&targetPosition, XMLoadFloat4(&m_SceneContext.pLights->GetDirectionalLight().position) + XMLoadFloat4(&m_SceneContext.pLights->GetDirectionalLight().direction));

	DebugRenderer::DrawLine(lightPosition, targetPosition, XMFLOAT4{ Colors::Green });
}

void CrashScene::Killzone(GameObject*, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Player" && action == PxTriggerAction::ENTER)
	{
		m_pCrash->PlayerDeath();
	}
}
