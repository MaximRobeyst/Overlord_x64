#pragma once
class MainMenuScene : public GameScene
{
public:
	MainMenuScene() : GameScene(L"Main menu") {}
	~MainMenuScene();

	MainMenuScene(const MainMenuScene& other) = delete;
	MainMenuScene(MainMenuScene&& other) noexcept = delete;
	MainMenuScene& operator=(const MainMenuScene& other) = delete;
	MainMenuScene& operator=(MainMenuScene&& other) noexcept = delete;
	
protected:
	void Initialize() override;
	void Update() override;
	void PostDraw() override;
	void OnGUI() override;

private:
	GameObject* m_pStartButton{ nullptr };
};
