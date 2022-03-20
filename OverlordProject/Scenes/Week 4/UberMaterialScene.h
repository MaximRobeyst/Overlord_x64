#pragma once

class UberMaterial;
class UberMaterialScene final : public GameScene
{
public:
	UberMaterialScene() : GameScene(L"UberMaterialScene") {};
	~UberMaterialScene() override = default;

	UberMaterialScene(const UberMaterialScene& other) = delete;
	UberMaterialScene(UberMaterialScene&& other) noexcept = delete;
	UberMaterialScene& operator=(const UberMaterialScene& other) = delete;
	UberMaterialScene& operator=(UberMaterialScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	UberMaterial* m_pUberMaterial;
	TransformComponent* m_pTransform;
	float m_Angle = 0.0f;
	float m_Speed = 25.f;
};

