#include "stdafx.h"
#include "SpriteTestScene.h"

void SpriteTestScene::Initialize()
{
	auto pGameObject = AddChild(new GameObject());
	auto pSpriteComponent = new SpriteComponent(L"Textures/TestSprite.jpg");
	pSpriteComponent->SetTexture(L"Textures/TestSprite.jpg");
	pGameObject->AddComponent(pSpriteComponent);
	
}

void SpriteTestScene::Update()
{
}

void SpriteTestScene::Draw()
{
}

void SpriteTestScene::OnGUI()
{
}
