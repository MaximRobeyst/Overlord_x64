#pragma once
class Crab : public GameObject
{
public:
	Crab(const XMFLOAT3& position1, const XMFLOAT3& position2);

	Crab(const Crab& other) = delete;
	Crab(Crab&& other) noexcept = delete;
	Crab& operator=(const Crab& other) = delete;
	Crab& operator=(Crab&& other) noexcept = delete;

	void Destroy();

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;
	void Draw(const SceneContext&) override;

private:
	void KillPlayer(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);

	std::vector<XMFLOAT3> m_Targets{};
	int m_CurrentIndex{ 0 };


	float m_Speed{ 0.5f };

	bool m_Hit{ false };
	
};

