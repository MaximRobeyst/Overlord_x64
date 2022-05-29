#include "stdafx.h"
#include "ParticleLifetime.h"

ParticleLifetime::ParticleLifetime(const XMFLOAT3& position, float lifetime)
	: m_LifeTime{lifetime}
{
	GetTransform()->Translate(position);
}

void ParticleLifetime::Initialize(const SceneContext&)
{
	//Particle System
	//Particle System
	ParticleEmitterSettings woodSettings{};
	woodSettings.maxVelocity = { 6.f,6.f,6.f };
	woodSettings.minVelocity = { -6.f, -6.f, -6.f };
	woodSettings.minSize = 1.f;
	woodSettings.maxSize = 2.f;
	woodSettings.minEnergy = 1.f;
	woodSettings.maxEnergy = 2.f;
	woodSettings.minScale = 1.f;
	woodSettings.maxScale = 1.f;
	woodSettings.minEmitterRadius = .2f;
	woodSettings.maxEmitterRadius = .5f;
	woodSettings.color = { 1.f,1.f,1.f, .6f };

	AddComponent(new ParticleEmitterComponent(L"Textures/Wood.png", woodSettings, 200));

}

void ParticleLifetime::Update(const SceneContext& sceneContext)
{
	m_Counter += sceneContext.pGameTime->GetElapsed();

	if (m_Counter >= m_LifeTime)
	{
		GetScene()->RemoveChild(this, true);
	}
}
