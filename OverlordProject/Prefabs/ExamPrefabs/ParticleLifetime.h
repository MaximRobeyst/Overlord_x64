#pragma once
class ParticleLifetime : public GameObject
{
public:
	ParticleLifetime(const XMFLOAT3& position, float lifetime = 3.0f);
	~ParticleLifetime() override = default;

	ParticleLifetime(const ParticleLifetime& other) = delete;
	ParticleLifetime(ParticleLifetime&& other) noexcept = delete;
	ParticleLifetime& operator=(const ParticleLifetime& other) = delete;
	ParticleLifetime& operator=(ParticleLifetime&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	float m_LifeTime{ 3.0f };
	float m_Counter{ 0.0f };
};

