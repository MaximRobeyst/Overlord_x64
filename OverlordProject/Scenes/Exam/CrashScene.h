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

	void GenerateMenu();
	void DestoyMenu();

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

	bool m_Paused{ false };

	Crash* m_pCrash{nullptr};
	PathCamera* m_pCamera{nullptr};
	SpriteFont* m_pFont{};
	GameObject* m_pMenu{ nullptr };

	std::vector<Crate*> m_pCrates;
	std::vector<GameObject*> m_pKillTriggers;

	FMOD::Sound* m_pTheme{};

	XMFLOAT3 m_LightPosition{ -96.f,66.1346436f,-41.1850471f };
};

