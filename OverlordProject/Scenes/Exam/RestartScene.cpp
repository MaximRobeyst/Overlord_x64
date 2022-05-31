#include "stdafx.h"
#include "RestartScene.h"
#include <Scenes\Exam\CrashScene.h>

void RestartScene::Initialize()
{
}

void RestartScene::Update()
{
	auto sceneManager = SceneManager::Get();

	auto pScene = SceneManager::Get()->GetScene(L"Crash bandicoot");
	sceneManager->RemoveGameScene(pScene, true);
	sceneManager->AddGameScene(new CrashScene());
	sceneManager->SetActiveGameScene(L"Crash bandicoot");
}
