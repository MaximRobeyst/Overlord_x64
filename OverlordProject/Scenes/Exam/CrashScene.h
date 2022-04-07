#pragma once

class Crash;
class CrashScene : public GameScene
{
public:
	CrashScene() : GameScene(L"Crash badicoot") {}
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
	enum InputIds
	{
		CharacterMoveLeft,
		CharacterMoveRight,
		CharacterMoveForward,
		CharacterMoveBackward,
		CharacterJump
	};

	Crash* m_pCrash{nullptr};
	SpriteFont* m_pFont{};
};

