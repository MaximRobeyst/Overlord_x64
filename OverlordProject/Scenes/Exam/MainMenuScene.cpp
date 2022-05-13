#include "stdafx.h"
#include "MainMenuScene.h"

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Initialize()
{
	m_pStartButton = AddChild(new GameObject());
	m_pStartButton->AddComponent(new SpriteComponent(L"Textures/LifeSprite.png", { 0.5, 0.5f }));
	m_pStartButton->GetTransform()->Translate(m_SceneContext.windowWidth - 175.f, 10.f, 0.f);

	auto header = AddChild(new GameObject());
	header->AddComponent(new SpriteComponent(L"Textures/Banner.png", { 0.5, 1.0f }));
	//header->GetTransform()->Translate();
	
}

void MainMenuScene::Update()
{
}

void MainMenuScene::PostDraw()
{
}

void MainMenuScene::OnGUI()
{
}
