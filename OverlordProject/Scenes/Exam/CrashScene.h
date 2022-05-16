#pragma once

class Crash;
class PathCamera;
class Crate;
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
	void PostDraw() override;
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

	bool m_DrawShadowMap{ true };
	float m_ShadowMapScale{ 0.1f };

	Crash* m_pCrash{nullptr};
	PathCamera* m_pCamera{nullptr};
	SpriteFont* m_pFont{};

	std::vector<Crate*> m_pCrates;

	FMOD::Sound* m_pTheme{};
};

