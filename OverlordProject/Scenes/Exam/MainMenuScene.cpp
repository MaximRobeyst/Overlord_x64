#include "stdafx.h"
#include "MainMenuScene.h"

#include <Materials\ColorMaterial.h>
#include <Materials\Shadow\DiffuseMaterial_Shadow.h>
#include <Materials\DiffuseMaterial_Skinned.h>
#include <Materials\Post\CRTEffect.h>
#include <Materials\Post\PostBlur.h>

#include "Prefabs\ExamPrefabs\Button.h"
#include <Materials\Skybox.h>

#include <Scenes\Exam\CrashScene.h>

bool MainMenuScene::m_PostProcessingOn{false};

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::PostProcessing()
{
	return m_PostProcessingOn;
}

void MainMenuScene::Initialize()
{

#ifdef _DEBUG
	m_SceneContext.settings.enableOnGUI = true;
#else
	m_SceneContext.settings.showInfoOverlay = false;
#endif // _DEBUG

	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Crash_Theme.wav", FMOD_LOOP_NORMAL, nullptr, &m_pTheme);
	SoundManager::Get()->GetSystem()->playSound(m_pTheme, nullptr, false, nullptr);

	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	m_SceneContext.pLights->SetDirectionalLight({ -96.f,66.1346436f,-41.1850471f }, { 0.740129888f, -0.597205281f, 0.309117377f });

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
	pModel->SetMaterial(pRockMaterial, 4);
	pModel->SetMaterial(pLeaveMaterial, 5);
	pModel->SetMaterial(pTreeMaterial, 6);
	pModel->SetMaterial(pPillarMaterial, 7);
	pModel->SetMaterial(pPillarMaterial, 8);
	pModel->SetMaterial(pTotemMaterial, 9);
	pLevel->GetTransform()->Rotate(90.f, 0.f, 0.0f);

	//m_pStartButton = AddChild(new GameObject());
	//m_pStartButton->AddComponent(new SpriteComponent(L"Textures/LifeSprite.png", { 0.5, 0.5f }));
	//m_pStartButton->GetTransform()->Translate(m_SceneContext.windowWidth - 175.f, 10.f, 0.f);

	auto pHeader = AddChild(new GameObject());
	pHeader->AddComponent(new SpriteComponent(L"Textures/Banner.png", XMFLOAT2{1.0f, -1.f}));
	pHeader->GetTransform()->Translate(0, m_SceneContext.windowHeight, 0.f);
	pHeader->GetTransform()->Scale(0.5f, 0.5f, 1.0f);
	
	m_pFixedCamera = AddChild(new FixedCamera());
	m_pFixedCamera->GetTransform()->Translate(0.75f, 1.3f, 0.84f);
	auto rotation = XMFLOAT4{ 0.025f, -0.115f, 0.0f, 1.f };
	auto cameraRotation = XMLoadFloat4(&rotation);

	m_pFixedCamera->GetTransform()->Rotate(cameraRotation);
	m_pFixedCamera->GetComponent<CameraComponent>()->SetActive(true);

	// Model
	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	material->SetDiffuseTexture(L"Textures/tex_crash.png");

	m_pHeader = AddChild(new GameObject());
	auto model = m_pHeader->AddComponent(new ModelComponent(L"Models/Character/Test_Character.ovm"));
	model->SetMaterial(material, 0);
	model->GetAnimator()->SetAnimation(0);
	model->GetAnimator()->Play();

	model->GetTransform()->Translate(0.6f, 0.5f, 2.0f);
	model->GetTransform()->Rotate(0, -30, 0);

	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/CrashALike_64.fnt");

	auto pButton = AddChild(new Button(L"Start", XMFLOAT2{ 250.f, 410.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 150.f, 50.f }));
	pButton->SetOnClickFunction([]() 
		{
			auto sceneManager = SceneManager::Get();

			auto pScene = SceneManager::Get()->GetScene(L"Crash bandicoot");
			sceneManager->RemoveGameScene(pScene, true);
			sceneManager->AddGameScene(new CrashScene());
			sceneManager->SetActiveGameScene(L"Crash bandicoot");
		});
	pButton = AddChild(new Button(L"Options", XMFLOAT2{ 250.f, 460.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 200.f, 50.f }));
	pButton->SetOnClickFunction([&]() {
		m_PostProcessingOn = !m_PostProcessingOn;
		m_PostProcessingState = m_PostProcessingOn ? L"On" : L"Off";

		if (m_PostProcessingOn)
		{
			m_pPostBlur = MaterialManager::Get()->CreateMaterial<PostBlur>();
			m_pBloom = MaterialManager::Get()->CreateMaterial<CRTEffect>();

			AddPostProcessingEffect(m_pBloom);
			AddPostProcessingEffect(m_pPostBlur);
		}
		else
		{
			RemovePostProcessingEffect(m_pPostBlur);
			RemovePostProcessingEffect(m_pBloom);
		}

		});
	pButton = AddChild(new Button(L"Quit", XMFLOAT2{ 250.f, 510.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 125.f, 50.f }));
	pButton->SetOnClickFunction([&]()
		{
			PostQuitMessage(0);
		});


	auto pSkybox = AddChild(new GameObject());
	pSkybox->GetTransform()->Scale(500.f, 500.f, 500.f);
	auto pSkyboxModel = pSkybox->AddComponent<ModelComponent>(new ModelComponent(L"Models/Cube.ovm"));
	auto pSkyboxMat = MaterialManager::Get()->CreateMaterial<Skybox>();
	pSkyboxModel->SetMaterial(pSkyboxMat);
}

void MainMenuScene::Update()
{
	if (m_pControls == nullptr)
	{
		m_pControls = AddChild(new GameObject());
		m_pControls->AddComponent<SpriteComponent>(new SpriteComponent(L"Textures/Controls.png", XMFLOAT2{ 1.f, 1.f }, XMFLOAT4{ Colors::White }));
		m_pControls->GetTransform()->Scale(0.15f);
		m_pControls->GetTransform()->Translate(0.f, 0.f, 0.f);
	}
}

void MainMenuScene::Draw()
{
	XMFLOAT2 offset{ 200.f, 400.f };

	TextRenderer::Get()->DrawText(m_pFont, m_PostProcessingState, XMFLOAT2{ 475.f, 460.f }, m_PostProcessingState == L"On" ? XMFLOAT4{ Colors::Green } : XMFLOAT4{ Colors::Red });

	//TextRenderer::Get()->DrawText(m_pFont, L"Start", XMFLOAT2{ offset.x + 50.f, offset.y + 10.f }, XMFLOAT4{ Colors::Orange });
	//TextRenderer::Get()->DrawText(m_pFont, L"Options", XMFLOAT2{	offset.x + 50.f, offset.y + 60.f }, XMFLOAT4{ Colors::Orange });
	//TextRenderer::Get()->DrawText(m_pFont, L"Quit",		XMFLOAT2{		offset.x + 50.f, offset.y + 110.f}, XMFLOAT4{Colors::Orange});
}

void MainMenuScene::OnGUI()
{
	float position[3] = { m_pHeader->GetTransform()->GetPosition().x, m_pHeader->GetTransform()->GetPosition().y, m_pHeader->GetTransform()->GetPosition().z };
	if (ImGui::InputFloat3("Header position", position))
		m_pHeader->GetTransform()->Translate(position[0], position[1], position[2]);

	static float rotation[3] = { 0.0f, 0.0f, 0.0f };
	if (ImGui::InputFloat3("Header rotation", rotation))
		m_pHeader->GetTransform()->Rotate(rotation[0], rotation[1], rotation[2]);
}
