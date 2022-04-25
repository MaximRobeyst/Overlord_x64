#pragma once
class Crash;
class Crate : public GameObject
{
public:
	enum class CrateType
	{
		Defaut_Crate,
		PowerUp_Crate,
		Jump_Crate,
		CheckPoint_Crate,
		UkaUka_Crate,
		TNT_Crate
	};

	Crate(const XMFLOAT3& position, CrateType cratetype = CrateType::Defaut_Crate, int lives = 9);
	~Crate() override;

	Crate(const Crate & other) = delete;
	Crate(Crate && other) noexcept = delete;
	Crate& operator=(const Crate & other) = delete;
	Crate& operator=(Crate && other) noexcept = delete;

	void Destoy(Crash* pCrash);

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	void OnBoxJump(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);

	XMFLOAT3 m_Position{};

	CrateType m_CrateType{ CrateType::Defaut_Crate };
	ParticleEmitterComponent* m_pEmmiter;

	int m_Lives{ 9 };
	bool m_Hit{ false };
};

