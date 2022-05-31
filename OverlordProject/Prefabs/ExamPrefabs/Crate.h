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
	void RenderGui();

	static float GetPercentageOfBoxes();

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	static int m_AmountOfBoxes;
	static int m_MaxAmountOfBoxes;

	void OnBoxJump(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
	void OnBoxHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);

	XMFLOAT3 m_Position{};

	CrateType m_CrateType{ CrateType::Defaut_Crate };
	ParticleEmitterComponent* m_pEmmiter;
	FMOD::Sound* m_pBounceSound{};
	FMOD::Sound* m_pCrateBreakSound{};

	int m_Lives{ 9 };
	bool m_Hit{ false };
};

