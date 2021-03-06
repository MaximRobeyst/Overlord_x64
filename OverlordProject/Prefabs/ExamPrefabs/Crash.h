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

	float maxMoveSpeed{ 10.f }; //Maximum Move
	float maxFallSpeed{ 10.f };

	float JumpSpeed{ 13.5f };

	float moveAccelerationTime{ .3f };
	float fallAccelerationTime{ .3f };

	PxCapsuleControllerDesc controller{};

	float rotationSpeed{ 60.f };

	float attackTime{ 1.0f };

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

	bool m_Attacking{ false };
	float m_AttackTimer{ 0.0f };
	float m_AttackLength{ 0.5f };
	float m_AttackRotationSpeed{ 2160.f };
	float m_CurrentAttackRotation{ 0.0f };

	float m_CurrentAngle{ 0.0f };

	int m_Lives{ 4 };
	XMFLOAT3 m_RespawnPosition;

	CameraComponent* m_pCameraComponent{};
	ControllerComponent* m_pControllerComponent{};
	ModelAnimator* m_pAnimator{};

	SpriteFont* m_pFont{};
	GameObject* m_pLifeSprite{};
	GameObject* m_pWumpaSprite{};
	GameObject* m_pModelObject{};

	FMOD::Sound* m_pAttackSound{};

	CrashDesc m_CharacterDesc;
	float m_TotalPitch{}, m_TotalYaw{}; //Total camera Pitch(X) and Yaw(Y) rotation
	float m_MoveAcceleration{}, //Acceleration required to reach maxMoveVelocity after 1 second (maxMoveVelocity / moveAccelerationTime)
		m_FallAcceleration{}, //Acceleration required to reach maxFallVelocity after 1 second (maxFallVelocity / fallAccelerationTime)
		m_MoveVelocity{}; //MoveVelocity > Horizontal Movement = MoveDirection * MoveVelocity
	float m_MoveSpeed{};

	XMFLOAT3 m_TotalVelocity{}; //TotalVelocity with X/Z for Horizontal Movement AND Y for Vertical Movement (fall/jump)
	XMFLOAT3 m_CurrentDirection{}; //Current/Last Direction based on Camera forward/right (Stored for deacceleration)

	float m_HitAngleOffset{ 11.25f / 2.0f };
	float m_HitRange{ 0.5f };
};

