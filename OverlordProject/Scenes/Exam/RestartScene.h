#pragma once
class RestartScene : public GameScene
{
public:
	RestartScene() : GameScene(L"Restart") {}

protected:
	void Initialize() override;
	void Update() override;
};

