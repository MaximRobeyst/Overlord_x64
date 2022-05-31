#pragma once
class YouWinScene : public GameScene
{
public:
	YouWinScene() :GameScene(L"YouWinScene") {}
	~YouWinScene() override = default;
	YouWinScene(const YouWinScene& other) = delete;
	YouWinScene(YouWinScene&& other) noexcept = delete;
	YouWinScene& operator=(const YouWinScene& other) = delete;
	YouWinScene& operator=(YouWinScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Draw() override;

	void OnSceneActivated() override;

private:
	SpriteFont* m_pFont;
	GameObject* m_pMenu;

	FixedCamera* m_pFixedCamera{ nullptr };

	XMFLOAT3 m_LightPosition{ -96.f,66.1346436f,-41.1850471f  + 100.f};
};

