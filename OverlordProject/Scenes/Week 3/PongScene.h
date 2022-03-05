#pragma once
class PongScene final : public GameScene
{
public:
	PongScene() : GameScene(L"PongScene") {};
	~PongScene() override = default;

	PongScene(const PongScene& other) = delete;
	PongScene(PongScene&& other) noexcept = delete;
	PongScene& operator=(const PongScene& other) = delete;
	PongScene& operator=(PongScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	GameObject* m_pPeddle1{};
	GameObject* m_pPeddle2{};
	GameObject* m_pBall{};

};