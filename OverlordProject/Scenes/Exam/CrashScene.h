#pragma once

class Crash;
class PathCamera;
class CrashScene : public GameScene
{
public:
	CrashScene() : GameScene(L"Crash bandicoot") {}
	~CrashScene() override;
	CrashScene(const CrashScene& other) = delete;
	CrashScene(CrashScene&& other) noexcept = delete;
	CrashScene& operator=(const CrashScene& other) = delete;
	CrashScene& operator=(CrashScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;
private:
	void Killzone(GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction action);

	enum InputIds
	{
		CharacterMoveLeft,
		CharacterMoveRight,
		CharacterMoveForward,
		CharacterMoveBackward,
		CharacterJump,
		CharacterAttack
	};

	Crash* m_pCrash{nullptr};
	PathCamera* m_pCamera{nullptr};
	SpriteFont* m_pFont{};

	FMOD::Sound* m_pTheme{};
};

