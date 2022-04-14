#pragma once
#include "Prefabs/Character.h"

struct CrashDesc
{
	CrashDesc(
		PxMaterial* pMaterial,
		float radius = .5f,
		float height = 2.f)
	{
		controller.setToDefault();
		controller.radius = radius;
		controller.height = height;
		controller.material = pMaterial;
	}

	float maxMoveSpeed{ 15.f }; //Maximum Move
	float maxFallSpeed{ 15.f };

	float JumpSpeed{ 15.f };

	float moveAccelerationTime{ .3f };
	float fallAccelerationTime{ .3f };

	PxCapsuleControllerDesc controller{};

	float rotationSpeed{ 60.f };

	float attackTime{ 2.0f };

	int actionId_MoveLeft{ -1 };
	int actionId_MoveRight{ -1 };
	int actionId_MoveForward{ -1 };
	int actionId_MoveBackward{ -1 };
	int actionId_Jump{ -1 };
	int actionId_Attack{ -1 };
};

class Crash : public GameObject
{
public:
	Crash(const CrashDesc& characterDesc);
	~Crash() override = default;

	Crash(const Crash& other) = delete;
	Crash(Crash&& other) noexcept = delete;
	Crash& operator=(const Crash& other) = delete;
	Crash& operator=(Crash&& other) noexcept = delete;

	void DrawImGui();

	void AddWumpaFruit();
	void AddLife();

	void PlayerDeath();
	void SetCheckpoint(XMFLOAT3 position);

	void Jump(const SceneContext& sceneContext);

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;
	void Draw(const SceneContext&) override;

private:
	void Attack(const SceneContext& sceneContext);

	bool IsGrounded();

	int m_WumpaNumber{};
	bool m_Grounded{ false };
	bool m_Active{ true };

	int m_Lives{ 4 };
	XMFLOAT3 m_RespawnPosition;

	CameraComponent* m_pCameraComponent{};
	ControllerComponent* m_pControllerComponent{};

	SpriteFont* m_pFont{};
	GameObject* m_pSprite{};
	GameObject* m_pModel{};

	CrashDesc m_CharacterDesc;
	float m_TotalPitch{}, m_TotalYaw{}; //Total camera Pitch(X) and Yaw(Y) rotation
	float m_MoveAcceleration{}, //Acceleration required to reach maxMoveVelocity after 1 second (maxMoveVelocity / moveAccelerationTime)
		m_FallAcceleration{}, //Acceleration required to reach maxFallVelocity after 1 second (maxFallVelocity / fallAccelerationTime)
		m_MoveVelocity{}; //MoveVelocity > Horizontal Movement = MoveDirection * MoveVelocity
	float m_MoveSpeed{};

	XMFLOAT3 m_TotalVelocity{}; //TotalVelocity with X/Z for Horizontal Movement AND Y for Vertical Movement (fall/jump)
	XMFLOAT3 m_CurrentDirection{}; //Current/Last Direction based on Camera forward/right (Stored for deacceleration)
};

