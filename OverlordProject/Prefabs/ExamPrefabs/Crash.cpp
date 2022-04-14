#include "stdafx.h"
#include "Crash.h"

#include <Materials/DiffuseMaterial.h>
#include <Prefabs/ExamPrefabs/PathCamera.h>

Crash::Crash(const CrashDesc& characterDesc) :
	m_CharacterDesc{ characterDesc },
	m_MoveAcceleration(characterDesc.maxMoveSpeed / characterDesc.moveAccelerationTime),
	m_FallAcceleration(characterDesc.maxFallSpeed / characterDesc.fallAccelerationTime)
{
	m_CharacterDesc.controller.stepOffset = 0.1f;
	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/CrashALike_64.fnt");

}

void Crash::DrawImGui()
{
	if (ImGui::CollapsingHeader("Character"))
	{
		ImGui::Text(std::format("Move Speed: {:0.1f} m/s", m_MoveSpeed).c_str());
		ImGui::Text(std::format("Fall Speed: {:0.1f} m/s", m_TotalVelocity.y).c_str());
		ImGui::Text(("Grounded: " + std::to_string(m_Grounded)).c_str() );

		ImGui::Text(std::format("Move Acceleration: {:0.1f} m/s2", m_MoveAcceleration).c_str());
		ImGui::Text(std::format("Fall Acceleration: {:0.1f} m/s2", m_FallAcceleration).c_str());

		const float jumpMaxTime = m_CharacterDesc.JumpSpeed / m_FallAcceleration;
		const float jumpMaxHeight = (m_CharacterDesc.JumpSpeed * jumpMaxTime) - (0.5f * (m_FallAcceleration * powf(jumpMaxTime, 2)));
		ImGui::Text(std::format("Jump Height: {:0.1f} m", jumpMaxHeight).c_str());

		ImGui::Dummy({ 0.f,5.f });
		if (ImGui::DragFloat("Max Move Speed (m/s)", &m_CharacterDesc.maxMoveSpeed, 0.1f, 0.f, 0.f, "%.1f") ||
			ImGui::DragFloat("Move Acceleration Time (s)", &m_CharacterDesc.moveAccelerationTime, 0.1f, 0.f, 0.f, "%.1f"))
		{
			m_MoveAcceleration = m_CharacterDesc.maxMoveSpeed / m_CharacterDesc.moveAccelerationTime;
		}

		ImGui::Dummy({ 0.f,5.f });
		if (ImGui::DragFloat("Max Fall Speed (m/s)", &m_CharacterDesc.maxFallSpeed, 0.1f, 0.f, 0.f, "%.1f") ||
			ImGui::DragFloat("Fall Acceleration Time (s)", &m_CharacterDesc.fallAccelerationTime, 0.1f, 0.f, 0.f, "%.1f"))
		{
			m_FallAcceleration = m_CharacterDesc.maxFallSpeed / m_CharacterDesc.fallAccelerationTime;
		}

		ImGui::Dummy({ 0.f,5.f });
		ImGui::DragFloat("Jump Speed", &m_CharacterDesc.JumpSpeed, 0.1f, 0.f, 0.f, "%.1f");
		ImGui::DragFloat("Rotation Speed (deg/s)", &m_CharacterDesc.rotationSpeed, 0.1f, 0.f, 0.f, "%.1f");

		bool isActive = m_Active;
		if (ImGui::Checkbox("Character Camera", &isActive))
		{
			m_Active = isActive;
		}
	}
}

void Crash::AddWumpaFruit()
{
	++m_WumpaNumber;
}

void Crash::AddLife()
{
	++m_Lives;
}

void Crash::PlayerDeath()
{
	--m_Lives;

	if (m_Lives < 0)
		Logger::LogInfo(L"Game Over!");

	GetTransform()->Translate(m_RespawnPosition);
	m_TotalVelocity.y = 0.f;
}

void Crash::SetCheckpoint(XMFLOAT3 position)
{
	m_RespawnPosition = position;
	m_RespawnPosition.y += 0.5f;
}

void Crash::Jump(const SceneContext& sceneContext)
{
	//Set m_TotalVelocity.y equal to CharacterDesc::JumpSpeed

	m_TotalVelocity.y = m_CharacterDesc.JumpSpeed * sceneContext.pGameTime->GetElapsed();
	m_Grounded = false;
}

void Crash::Initialize(const SceneContext& sceneContext)
{
	SetTag(L"Player");
	//Controller
	m_pControllerComponent = AddComponent(new ControllerComponent(m_CharacterDesc.controller));

	//Camera
	
	//m_pCameraComponent = pCamera->GetComponent<CameraComponent>();
	//m_pCameraComponent->SetActive(true); //Uncomment to make this camera the active camera

	// Model

	m_pModel = AddChild(new GameObject());
	auto model = m_pModel->AddComponent(new ModelComponent(L"Models/Crash.ovm"));
	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	material->SetDiffuseTexture(L"Textures/tex_crash.png");
	model->SetMaterial(material);

	m_pModel->GetTransform()->Rotate(XMFLOAT3{ 0, 180.0f, 0.0f });
	m_pModel->GetTransform()->Translate(XMFLOAT3{ 0.0f, -m_CharacterDesc.controller.height * .5f, 0.f });
	//pCamera->GetTransform()->Translate(0.f, m_CharacterDesc.controller.height * 1.25f, -5.f);

	m_pSprite = AddChild(new GameObject());
	m_pSprite->AddComponent(new SpriteComponent(L"Textures/LifeSprite.png", { 0.5, 0.5f }));
	m_pSprite->GetTransform()->Translate(sceneContext.windowWidth - 175.f, 10.f, 0.f);

	SetCheckpoint(GetTransform()->GetPosition());
}

void Crash::Update(const SceneContext& sceneContext)
{
	if (m_Active)
	{
		//constexpr float epsilon{ 0.01f }; //Constant that can be used to compare if a float is near zero

		//***************
		//HANDLE INPUT

		//## Input Gathering (move)
		XMFLOAT2 move{};
		//move.y should contain a 1 (Forward) or -1 (Backward) based on the active input (check corresponding actionId in m_CharacterDesc)
		//Optional: if move.y is near zero (abs(move.y) < epsilon), you could use the ThumbStickPosition.y for movement
		if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveForward))
			move.y = 1;
		if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveBackward))
			move.y = -1;

		//move.x should contain a 1 (Right) or -1 (Left) based on the active input (check corresponding actionId in m_CharacterDesc)
		//Optional: if move.x is near zero (abs(move.x) < epsilon), you could use the Left ThumbStickPosition.x for movement
		if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveRight))
			move.x = 1;
		if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveLeft))
			move.x = -1;

		//## Input Gathering (look)
		XMFLOAT2 look{ 0.f, 0.f }; //Uncomment
		//Only if the Left Mouse Button is Down >
			// Store the MouseMovement in the local 'look' variable (cast is required)
		//Optional: in case look.x AND look.y are near zero, you could use the Right ThumbStickPosition for look
		if (sceneContext.pInput->IsMouseButton(InputState::down, VK_LBUTTON))
		{
			look.x = (float)InputManager::GetMouseMovement().x;
			look.y = (float)InputManager::GetMouseMovement().y;
		}

		if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_Attack)) Attack(sceneContext);

		//************************
		//GATHERING TRANSFORM INFO

		//Retrieve the TransformComponent
		TransformComponent* transformComponent = GetTransform();
		//Retrieve the forward & right vector (as XMVECTOR) from the TransformComponent
		XMVECTOR forward = XMLoadFloat3(&transformComponent->GetForward());
		XMVECTOR right = XMLoadFloat3(&transformComponent->GetRight());

		//***************
		//CAMERA ROTATION

		//Adjust the TotalYaw (m_TotalYaw) & TotalPitch (m_TotalPitch) based on the local 'look' variable
		//m_TotalYaw += look.y * sceneContext.pGameTime->GetElapsed() * m_CharacterDesc.rotationSpeed;
		//m_TotalPitch += look.x * sceneContext.pGameTime->GetElapsed() * m_CharacterDesc.rotationSpeed;
		//Make sure this calculated on a framerate independent way and uses CharacterDesc::rotationSpeed.
		//Rotate this character based on the TotalPitch (X) and TotalYaw (Y)
		MathHelper::Clamp(m_TotalYaw, 90.f, -90.f);

		transformComponent->Rotate(m_TotalYaw, m_TotalPitch, 0.f, true);

		//********
		//MOVEMENT

		//## Horizontal Velocity (Forward/Backward/Right/Left)
		//Calculate the current move acceleration for this frame (m_MoveAcceleration * ElapsedTime)
		//If the character is moving (= input is pressed)
		if (move.x != 0 || move.y != 0)
		{
			//Calculate & Store the current direction (m_CurrentDirection) >> based on the forward/right vectors and the pressed input
			XMVECTOR newDirection = (forward * move.y) + (right * move.x);


			XMStoreFloat3(&m_CurrentDirection, newDirection);
			//Increase the current MoveSpeed with the current Acceleration (m_MoveSpeed)
			m_MoveSpeed += m_MoveAcceleration * sceneContext.pGameTime->GetElapsed();

			//Make sure the current MoveSpeed stays below the maximum MoveSpeed (CharacterDesc::maxMoveSpeed) 
			MathHelper::Clamp(m_MoveSpeed, m_CharacterDesc.maxMoveSpeed, 0.f);

			//float angle{};
			//XMStoreFloat(&angle, XMVector3AngleBetweenNormals(-XMLoadFloat3(&m_pModel->GetTransform()->GetForward()), XMVector3Normalize(newDirection)));
			//m_pModel->GetTransform()->Rotate(0, angle, 0, false);
		}
		//Else (character is not moving, or stopped moving)
		else
		{
			//Decrease the current MoveSpeed with the current Acceleration (m_MoveSpeed)
			m_MoveSpeed -= m_MoveAcceleration * sceneContext.pGameTime->GetElapsed(); ;

			//Make sure the current MoveSpeed doesn't get smaller than zero
			MathHelper::Clamp(m_MoveSpeed, m_CharacterDesc.maxMoveSpeed, 0.f);
			//m_pModel->GetTransform()->Rotate(0, 0.0f, 0);
		}
		//Now we can calculate the Horizontal Velocity which should be stored in m_TotalVelocity.xz
		//Calculate the horizontal velocity (m_CurrentDirection * MoveSpeed)
		XMVECTOR newVelocity = XMLoadFloat3(&m_CurrentDirection);
		XMFLOAT3 velocity{};
		XMStoreFloat3(&velocity, newVelocity * m_MoveSpeed * sceneContext.pGameTime->GetElapsed());

		//Set the x/z component of m_TotalVelocity (horizontal_velocity x/z)
		//It's important that you don't overwrite the y component of m_TotalVelocity (contains the vertical velocity)
		m_TotalVelocity.x = velocity.x;
		m_TotalVelocity.z = velocity.z;

		//## Vertical Movement (Jump/Fall)
		//If the Controller Component is NOT grounded (= freefall)
		m_Grounded = IsGrounded(); //m_pControllerComponent->GetCollisionFlags() == PxControllerCollisionFlag::eCOLLISION_DOWN;
		if (!m_Grounded)
		{
			//Decrease the y component of m_TotalVelocity with a fraction (ElapsedTime) of the Fall Acceleration (m_FallAcceleration)
			m_TotalVelocity.y -= m_FallAcceleration * (sceneContext.pGameTime->GetElapsed() * sceneContext.pGameTime->GetElapsed());
			//Make sure that the minimum speed stays above -CharacterDesc::maxFallSpeed (negative!)
			if (m_TotalVelocity.y < -m_CharacterDesc.maxFallSpeed)
			{
				m_TotalVelocity.y = -m_CharacterDesc.maxFallSpeed;
			}

			//if (m_pControllerComponent->GetCollisionFlags() == PxControllerCollisionFlag::eCOLLISION_DOWN)
			//	m_Grounded = true;
		}
		//Else If the jump action is triggered
		else if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_Jump))
		{
			//Set m_TotalVelocity.y equal to CharacterDesc::JumpSpeed
			//m_TotalVelocity.y = m_CharacterDesc.JumpSpeed * sceneContext.pGameTime->GetElapsed();
			//m_Grounded = false;

			Jump(sceneContext);
		}
		//Else (=Character is grounded, no input pressed)
		else
		{
			//m_TotalVelocity.y is zero
			//m_TotalVelocity.y = 0;
		}

		//************
		//DISPLACEMENT

		//The displacement required to move the Character Controller (ControllerComponent::Move) can be calculated using our TotalVelocity (m/s)
		//Calculate the displacement (m) for the current frame and move the ControllerComponent
		m_pControllerComponent->Move(m_TotalVelocity);

		//The above is a simple implementation of Movement Dynamics, adjust the code to further improve the movement logic and behaviour.
		//Also, it can be usefull to use a seperate RayCast to check if the character is grounded (more responsive)
	}
}

void Crash::Draw(const SceneContext& sceneContext)
{
	TextRenderer::Get()->DrawText(m_pFont, std::to_wstring(m_WumpaNumber), XMFLOAT2{ 50.f, 10.f }, XMFLOAT4{ Colors::Orange });
	TextRenderer::Get()->DrawText(m_pFont, std::to_wstring(m_Lives), XMFLOAT2{ sceneContext.windowWidth - 100.f, 10.f }, XMFLOAT4{ Colors::Orange });
}

void Crash::Attack(const SceneContext& /*sceneContext*/)
{
	Logger::LogInfo(L"Player is attacking");


	//SceneManager::Get()->GetActiveScene()
}

bool Crash::IsGrounded()
{
	PxVec3 rayStart = PxVec3{ m_pControllerComponent->GetFootPosition().x, m_pControllerComponent->GetFootPosition().y + .1f ,m_pControllerComponent->GetFootPosition().z };
	PxVec3 rayDir{ 0, -1, 0 };
	float distance{ m_CharacterDesc.controller.stepOffset + m_CharacterDesc.controller.stepOffset };

	PxQueryFilterData filterData{};
	filterData.data.word0 = ~UINT(CollisionGroup::None);
	PxRaycastBuffer hit{};

	DebugRenderer::DrawLine(m_pControllerComponent->GetFootPosition(), XMFLOAT3{ rayStart.x + 0, rayStart.y -1 * distance, rayStart.z + 0 }, XMFLOAT4{ Colors::Red });
	return GetScene()->GetPhysxProxy()->Raycast(rayStart, rayDir, distance, hit);
}
