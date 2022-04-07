#include "stdafx.h"
#include "CrashScene.h"

// Materials
#include <Materials/DiffuseMaterial.h>

// Prefabs
#include <Prefabs/ExamPrefabs/Crash.h>
#include <Prefabs/ExamPrefabs/WumpaFruit.h>
#include <Prefabs/ExamPrefabs/Crate.h>

CrashScene::~CrashScene()
{
}

void CrashScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	//Ground Plane
	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	//Character
	CharacterDesc characterDesc{ pDefaultMaterial, 0.25f, 1.0f };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;

	m_pCrash = AddChild(new Crash(characterDesc));
	m_pCrash->GetTransform()->Translate(0.f, 5.f, 0.f);

	for (int i = 0; i < 20; ++i)
	{
		AddChild(new WumpaFruit(XMFLOAT3{ 0.f, .5f, 1.f + 10.f * i}));
	}
	GameObject* pCrate;
	for (int i = 0; i < 20; ++i)
	{
		pCrate = AddChild(new Crate());
	}

	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/CrashALike_32.fnt");

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
}

void CrashScene::Update()
{
	TextRenderer::Get()->DrawText(m_pFont, std::to_wstring(m_pCrash->GetWumpaFruit()), XMFLOAT2{50.f, 50.f}, XMFLOAT4{Colors::Orange});
}

void CrashScene::OnGUI()
{
	m_pCrash->DrawImGui();
}
