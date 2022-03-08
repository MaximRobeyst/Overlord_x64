#pragma once

class SpikeMaterial;
class SpikyScene : public GameScene
{
public:
	SpikyScene() : GameScene(L"SpikyScene") {};
	~SpikyScene() override = default;

	SpikyScene(const SpikyScene& other) = delete;
	SpikyScene(SpikyScene&& other) noexcept = delete;
	SpikyScene& operator=(const SpikyScene& other) = delete;
	SpikyScene& operator=(SpikyScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	SpikeMaterial* m_pSpikeMaterial;
};

