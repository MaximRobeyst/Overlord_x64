#pragma once
class Sound;
class OneUpPickup : public GameObject
{
public:
	OneUpPickup(XMFLOAT3 position);
	~OneUpPickup() override = default;

	OneUpPickup(const OneUpPickup& other) = delete;
	OneUpPickup(OneUpPickup&& other) noexcept = delete;
	OneUpPickup& operator=(const OneUpPickup& other) = delete;
	OneUpPickup& operator=(OneUpPickup&& other) noexcept = delete;
protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	XMFLOAT3 m_Position;
	bool deleteObject{ false };

	FMOD::Sound* m_pSound{ nullptr };

	void CollectLife(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
};

