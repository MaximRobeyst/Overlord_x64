#include "stdafx.h"
#include "GameOverScene.h"

#include <Prefabs/ExamPrefabs/Button.h>
#include <Scenes\Exam\MainMenuScene.h>

#include <Materials\Post\CRTEffect.h>
#include <Materials\Post\PostBlur.h>
#include <Materials\DiffuseMaterial_Skinned.h>
#include <Materials\ColorMaterial.h>
#include <Materials\Shadow\DiffuseMaterial_Shadow.h>
#include <Materials\Skybox.h>

#include <Scenes\Exam\CrashScene.h>

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
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
	pHeader->AddComponent(new SpriteComponent(L"Textures/Banner.png", XMFLOAT2{ 1.0f, -1.f }));
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

	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/CrashALike_64.fnt");

	auto pButton = AddChild(new Button(L"Restart", XMFLOAT2{ 250.f, 410.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 150.f, 50.f }));
	pButton->SetOnClickFunction([]()
		{
			auto sceneManager = SceneManager::Get();

			auto pScene = SceneManager::Get()->GetScene(L"Crash bandicoot");
			sceneManager->RemoveGameScene(pScene, true);
			sceneManager->AddGameScene(new CrashScene());
			sceneManager->SetActiveGameScene(L"Crash bandicoot");
		});

	pButton = AddChild(new Button(L"Quit", XMFLOAT2{ 250.f, 460.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 125.f, 50.f }));
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

void GameOverScene::Update()
{
}

void GameOverScene::Draw()
{
	TextRenderer::Get()->DrawText(m_pFont, L"Game Over!", XMFLOAT2{ (m_SceneContext.windowWidth / 2.f) - 200.f, 50.f}, XMFLOAT4{Colors::Orange});
}

void GameOverScene::OnGUI()
{
}

void GameOverScene::OnSceneActivated()
{
	if (MainMenuScene::PostProcessing())
	{
		auto pBlur = MaterialManager::Get()->CreateMaterial<PostBlur>();
		auto pCRTEffect = MaterialManager::Get()->CreateMaterial<CRTEffect>();

		AddPostProcessingEffect(pCRTEffect);
		AddPostProcessingEffect(pBlur);
	}
	else
	{
		ClearPostProcessing();
	}
}
