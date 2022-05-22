#include "stdafx.h"
#include "GameOverScene.h"

#include <Prefabs/ExamPrefabs/Button.h>

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	auto pButton = AddChild(new Button(L"Start", XMFLOAT2{ 250.f, 410.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 150.f, 50.f }));
	pButton->SetOnClickFunction([]()
		{
			SceneManager::Get()->PreviousScene();
		});
	pButton = AddChild(new Button(L"Main Menu", XMFLOAT2{ 250.f, 460.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 200.f, 50.f }));
	pButton->SetOnClickFunction([&]()
		{
			SceneManager::Get()->SetActiveGameScene(L"Main menu");
		});
	pButton = AddChild(new Button(L"Quit", XMFLOAT2{ 250.f, 510.f }, XMFLOAT4{ Colors::Orange }, XMFLOAT2{ 125.f, 50.f }));
	pButton->SetOnClickFunction([&]()
		{
			PostQuitMessage(1);
		});
}

void GameOverScene::Update()
{
}

void GameOverScene::Draw()
{
}

void GameOverScene::OnGUI()
{
}
