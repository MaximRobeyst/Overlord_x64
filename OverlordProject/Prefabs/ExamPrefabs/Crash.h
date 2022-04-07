#pragma once
#include "Prefabs/Character.h"

class Crash : public GameObject
{
public:
	Crash(const CharacterDesc& characterDesc);
	~Crash() override = default;

	Crash(const Crash& other) = delete;
	Crash(Crash&& other) noexcept = delete;
	Crash& operator=(const Crash& other) = delete;
	Crash& operator=(Crash&& other) noexcept = delete;

	void DrawImGui();

	void AddWumpaFruit();
	int GetWumpaFruit() const;

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	int m_WumpaNumber{};
	bool m_Grounded{};

	CameraComponent* m_pCameraComponent{};
	ControllerComponent* m_pControllerComponent{};

	CharacterDesc m_CharacterDesc;
	float m_TotalPitch{}, m_TotalYaw{}; //Total camera Pitch(X) and Yaw(Y) rotation
	float m_MoveAcceleration{}, //Acceleration required to reach maxMoveVelocity after 1 second (maxMoveVelocity / moveAccelerationTime)
		m_FallAcceleration{}, //Acceleration required to reach maxFallVelocity after 1 second (maxFallVelocity / fallAccelerationTime)
		m_MoveVelocity{}; //MoveVelocity > Horizontal Movement = MoveDirection * MoveVelocity
	float m_MoveSpeed{};

	XMFLOAT3 m_TotalVelocity{}; //TotalVelocity with X/Z for Horizontal Movement AND Y for Vertical Movement (fall/jump)
	XMFLOAT3 m_CurrentDirection{}; //Current/Last Direction based on Camera forward/right (Stored for deacceleration)
};

