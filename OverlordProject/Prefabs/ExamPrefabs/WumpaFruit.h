#pragma once
class Sound;
class WumpaFruit : public GameObject
{
public:
	WumpaFruit(XMFLOAT3 position);
	~WumpaFruit() override = default;

	WumpaFruit(const WumpaFruit& other) = delete;
	WumpaFruit(WumpaFruit && other) noexcept = delete;
	WumpaFruit& operator=(const WumpaFruit & other) = delete;
	WumpaFruit& operator=(WumpaFruit && other) noexcept = delete;
protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	XMFLOAT3 m_Position;
	bool deleteObject{false};

	FMOD::Sound* m_pSound{nullptr};

	void CollectFruit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
};

