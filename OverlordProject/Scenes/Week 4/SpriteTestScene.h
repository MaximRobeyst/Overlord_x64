#pragma once
class SpriteTestScene final : public GameScene
{
public:
	SpriteTestScene() : GameScene(L"SpriteTestScene") {};
	~SpriteTestScene() override = default;

	SpriteTestScene(const SpriteTestScene& other) = delete;
	SpriteTestScene(SpriteTestScene&& other) noexcept = delete;
	SpriteTestScene& operator=(const SpriteTestScene& other) = delete;
	SpriteTestScene& operator=(SpriteTestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
};

