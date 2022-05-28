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
#include <Prefabs/ExamPrefabs/Button.h>

#include <Materials/ColorMaterial.h>
#include <Materials/Shadow/DiffuseMaterial_Shadow.h>
#include <Materials/Skybox.h>
#include <Materials/Post/Bloom.h>


CrashScene::~CrashScene()
{
}

void CrashScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	//m_pBloom = MaterialManager::Get()->CreateMaterial<Bloom>();

	//AddPostProcessingEffect(m_pBloom);

	m_SceneContext.pLights->SetDirectionalLight( m_LightPosition, {0.740129888f, -0.597205281f, 0.309117377f});
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

	m_pCrates.push_back(new Crate(XMFLOAT3{ -1.0f, 0.f, 2.0f }));
	AddChild(m_pCrates.back());


	m_pCrates.push_back(new Crate(XMFLOAT3{ -1.0f, 0.f, 5.0f }));
	AddChild(m_pCrates.back());

	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.0f, 0.f, 3.5f }, Crate::CrateType::PowerUp_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -2.75f, -3.75f, 38.f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.0f, -3.f, 60.f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.0f, 0.0f, 60.f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -2.75f, 0.65f, 67.5f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -.25f, 0.f, 102.5f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -.25f, 0.75f, 102.5f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -1.75f, 5.15f, 111.85f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.3f, 7.1f, 113.850f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.3f, 7.1f, 112.6f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 2.05f, 7.1f, 112.6f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 2.05f, 7.1f, 113.850f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -3.0f, 9.15f, 114.75f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -.25f, 12.75f, 118.5f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ 1.25f, 12.75f, 122.f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());
	m_pCrates.push_back(new Crate(XMFLOAT3{ -1.75f, 12.75f, 127.f }, Crate::CrateType::CheckPoint_Crate, 1));
	AddChild(m_pCrates.back());


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

	auto pTotemMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pTotemMaterial->SetDiffuseTexture(L"Textures/Level_Textures/lambert4_albedo.jpeg");

	pModel->SetMaterial(pSandMaterial, 0);
	pModel->SetMaterial(pBrickMaterial, 1);
	pModel->SetMaterial(pShipMaterial, 2);
	pModel->SetMaterial(pTempleMaterial, 3);
	pModel->SetMaterial(pRockMaterial , 4);
	pModel->SetMaterial(pLeaveMaterial, 5);
	pModel->SetMaterial(pTreeMaterial, 6);
	pModel->SetMaterial(pPillarMaterial, 7);
	pModel->SetMaterial(pPillarMaterial, 8);
	pModel->SetMaterial(pTotemMaterial, 9);
	//pModel->SetMaterial(pTempleMaterial, 8);



	auto pSkybox = AddChild(new GameObject());
	pSkybox->GetTransform()->Scale(500.f,500.f, 500.f);
	auto pSkyboxModel = pSkybox->AddComponent<ModelComponent>(new ModelComponent(L"Models/Cube.ovm"));
	auto pSkyboxMat = MaterialManager::Get()->CreateMaterial<Skybox>();
	pSkyboxModel->SetMaterial(pSkyboxMat);

	auto pRigidbody = new RigidBodyComponent(true);
	auto triangleMesh = ContentManager::Load<PxTriangleMesh>(L"Models/Level/Level_Collision.ovpt");
	pRigidbody->AddCollider(PxTriangleMeshGeometry{ triangleMesh }, *pDefaultMaterial, false);
	pLevel->AddComponent(pRigidbody);

	pLevel->GetTransform()->Rotate(90.f, 0.f, 0.0f);

	
	auto pKillTrigger = AddChild(new GameObject());
	pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
	pRigidbody->AddCollider(PxBoxGeometry{ 5.f, 2.f, 2.f }, * pDefaultMaterial, true);
	pKillTrigger->GetTransform()->Translate(0, -7.5f, 31.5f);
	pKillTrigger->SetOnTriggerCallBack(std::bind(&CrashScene::Killzone, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_pKillTriggers.emplace_back(pKillTrigger);

	pKillTrigger = AddChild(new GameObject());
	pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
	pRigidbody->AddCollider(PxBoxGeometry{ 5.f, 2.f, 2.f }, * pDefaultMaterial, true);
	pKillTrigger->GetTransform()->Translate(0, -7.5f, 48.9f);
	pKillTrigger->SetOnTriggerCallBack(std::bind(&CrashScene::Killzone, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_pKillTriggers.emplace_back(pKillTrigger);
	pKillTrigger = AddChild(new GameObject());
	pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
	pRigidbody->AddCollider(PxBoxGeometry{ 5.f, 2.f, 2.f }, * pDefaultMaterial, true);
	pKillTrigger->GetTransform()->Translate(0, -7.5f, 83.5f);
	pKillTrigger->SetOnTriggerCallBack(std::bind(&CrashScene::Killzone, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_pKillTriggers.emplace_back(pKillTrigger);
	pKillTrigger = AddChild(new GameObject());
	pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
	pRigidbody->AddCollider(PxBoxGeometry{ 5.f, 2.f, 2.f }, * pDefaultMaterial, true);
	pKillTrigger->GetTransform()->Translate(0, -7.5f, 93.750f);
	pKillTrigger->SetOnTriggerCallBack(std::bind(&CrashScene::Killzone, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_pKillTriggers.emplace_back(pKillTrigger);


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
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::pressed, VK_ESCAPE))
	{
		if (m_Paused)
		{
			DestoyMenu();
			m_Paused = false;
			m_SceneContext.pGameTime->Start();
		}
		else
		{
			GenerateMenu();
			m_Paused = true;
			m_SceneContext.pGameTime->Stop();
		}
	}

	if (!m_Paused && m_pMenu != nullptr)
	{
		DestoyMenu();
	}

	m_SceneContext.pLights->GetDirectionalLight().position.z = m_LightPosition.z + m_pCrash->GetTransform()->GetPosition().z;
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
	float position[3]{ m_SceneContext.pLights->GetDirectionalLight().position.x, m_SceneContext.pLights->GetDirectionalLight().position.y, m_SceneContext.pLights->GetDirectionalLight().position.z };
	if (ImGui::InputFloat3("Camera position: ", position))
	{
		XMFLOAT4 directionalLightPosition{ position[0], position[1], position[2], m_SceneContext.pLights->GetDirectionalLight().position.w };
		m_SceneContext.pLights->GetDirectionalLight().position = directionalLightPosition;
	}

	m_pCrash->DrawImGui();
	m_pCamera->DrawImGui();

	if (m_pMenu != nullptr)
	{
		float menuPosition[3] = { m_pMenu->GetTransform()->GetPosition().x,  m_pMenu->GetTransform()->GetPosition().y,  m_pMenu->GetTransform()->GetPosition().z };

		if (ImGui::InputFloat3("Menu position", menuPosition))
		{
			m_pMenu->GetTransform()->Translate(menuPosition[0], menuPosition[1], menuPosition[2]);
		}
	}
	
	if (ImGui::CollapsingHeader("Crates"))
	{
		for (int i = 0; i < m_pCrates.size(); ++i)
		{
			float cratePosition[3] = { m_pCrates[i]->GetTransform()->GetPosition().x,  m_pCrates[i]->GetTransform()->GetPosition().y,  m_pCrates[i]->GetTransform()->GetPosition().z};
			
			if (ImGui::InputFloat3( ("Crate position" + std::to_string(i)).c_str(), cratePosition))
			{
				m_pCrates[i]->GetTransform()->Translate(cratePosition[0], cratePosition[1], cratePosition[2]);
			}
		}
		if (ImGui::Button("Add Crates"))
		{
			m_pCrates.push_back(new Crate(m_pCrates.back()->GetTransform()->GetPosition()));
			AddChild(m_pCrates.back());
		}
	}

	if (ImGui::CollapsingHeader("Killzones"))
	{
		for (int i = 0; i < m_pKillTriggers.size(); ++i)
		{
			float killzonePosition[3] = { m_pKillTriggers[i]->GetTransform()->GetPosition().x,  m_pKillTriggers[i]->GetTransform()->GetPosition().y,  m_pKillTriggers[i]->GetTransform()->GetPosition().z };

			if (ImGui::InputFloat3(("Killzone position" + std::to_string(i)).c_str(), killzonePosition))
			{
				m_pKillTriggers[i]->GetTransform()->Translate(killzonePosition[0], killzonePosition[1], killzonePosition[2]);
			}
		}
		if (ImGui::Button("Add Killzone"))
		{
			const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
			auto pKillTrigger = AddChild(new GameObject());
			auto pRigidbody = pKillTrigger->AddComponent(new RigidBodyComponent(true));
			pRigidbody->AddCollider(PxBoxGeometry{ 5.f, 2.f, 2.f }, *pDefaultMaterial, true);
			pKillTrigger->GetTransform()->Translate(0, -7.5f, 0.f);
			pKillTrigger->SetOnTriggerCallBack(std::bind(&CrashScene::Killzone, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			m_pKillTriggers.emplace_back(pKillTrigger);
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
		m_pCamera->ResetCamera();
	}
}

void CrashScene::GenerateMenu()
{
	// Pause menu
	m_pMenu = AddChild(new GameObject());
	auto pSpriteComponent = m_pMenu->AddComponent(new SpriteComponent(L"Textures/Panel.png", XMFLOAT2{ 0.5f, 0.5f }));
	m_pMenu->GetTransform()->Scale(0.35f);
	m_pMenu->GetTransform()->Translate( 
		(m_SceneContext.windowWidth / 2.0f) -( (pSpriteComponent->GetScale().x / 2.0f) * 0.35f), 
		(m_SceneContext.windowHeight / 2.0f) -( (pSpriteComponent->GetScale().y / 2.0f) * 0.35f), 0.f);

	auto pButton = m_pMenu->AddChild(new Button(
		L"Resume",
		XMFLOAT2{ (m_SceneContext.windowWidth/2.f) - 100.f , (m_SceneContext.windowHeight / 2.f) - 75.f },
		XMFLOAT4{ Colors::Orange },
		XMFLOAT2{ 200.f, 50.f })
	);
	pButton->SetOnClickFunction([&]()
		{
			m_Paused = false;
			m_SceneContext.pGameTime->Start();
		});
	pButton = m_pMenu->AddChild(new Button(
		L"Main Menu",
		XMFLOAT2{ (m_SceneContext.windowWidth / 2.f) -150.f, (m_SceneContext.windowHeight / 2.f) },
		XMFLOAT4{ Colors::Orange },
		XMFLOAT2{ 300.f, 50.f })
	);

	pButton->SetOnClickFunction([&]()
		{
			SceneManager::Get()->SetActiveGameScene(L"Main menu");
		});
	pButton = m_pMenu->AddChild(new Button(
		L"Quit",
		XMFLOAT2{ (m_SceneContext.windowWidth / 2.f) - 62.5f ,  (m_SceneContext.windowHeight / 2.f) + 75.f},
		XMFLOAT4{ Colors::Orange },
		XMFLOAT2{ 125.f, 50.f })
	);
	pButton->SetOnClickFunction([&]()
		{
			PostQuitMessage(1);
		});
}

void CrashScene::DestoyMenu()
{
	for (auto& child : m_pMenu->GetChildren<GameObject>())
	{
		m_pMenu->RemoveChild(child, true);
	}

	RemoveChild(m_pMenu, true);
	
	m_pMenu = nullptr;
}
