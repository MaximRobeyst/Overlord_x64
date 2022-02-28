#pragma once
class TestScene : public GameScene
{
public:
	TestScene() : GameScene(L"TestScene") {};
	~TestScene() = default;
	TestScene(const TestScene&) = delete;
	TestScene(TestScene&&) = delete;
	TestScene operator=(const TestScene&) = delete;
	TestScene operator=(TestScene&&) = delete;

protected:
		void Initialize() override;
};

