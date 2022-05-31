#pragma once

class PostBlur;
class CRTEffect;

class MainMenuScene : public GameScene
{
public:
	MainMenuScene() : GameScene(L"Main menu") {}
	~MainMenuScene();

	MainMenuScene(const MainMenuScene& other) = delete;
	MainMenuScene(MainMenuScene&& other) noexcept = delete;
	MainMenuScene& operator=(const MainMenuScene& other) = delete;
	MainMenuScene& operator=(MainMenuScene&& other) noexcept = delete;

	static bool PostProcessing();
	
protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	GameObject* m_pStartButton{ nullptr };
	GameObject* m_pHeader{ nullptr };

	SpriteFont* m_pFont{};
	FixedCamera* m_pFixedCamera{ nullptr };

	static bool m_PostProcessingOn;
	std::wstring m_PostProcessingState{ L"Off" };

	PostBlur* m_pPostBlur{};
	CRTEffect* m_pBloom{};
};

