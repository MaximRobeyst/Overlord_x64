#pragma once
class GameOverScene : public GameScene
{
public:
	GameOverScene() : GameScene(L"Game Over") {}
	~GameOverScene();

	GameOverScene(const GameOverScene& other) = delete;
	GameOverScene(GameOverScene&& other) noexcept = delete;
	GameOverScene& operator=(const GameOverScene& other) = delete;
	GameOverScene& operator=(GameOverScene&& other) noexcept = delete;

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
};

