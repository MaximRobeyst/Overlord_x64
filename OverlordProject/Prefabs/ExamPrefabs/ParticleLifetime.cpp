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
	ParticleEmitterSettings settings{};
	settings.velocity = { 0.f,1.f,0.f };
	settings.minSize = .1f;
	settings.maxSize = .2f;
	settings.minEnergy = 1.f;
	settings.maxEnergy = 2.f;
	settings.minScale = 0.1f;
	settings.maxScale = 0.2f;
	settings.minEmitterRadius = .2f;
	settings.maxEmitterRadius = .5f;
	settings.color = { 1.f,1.f,1.f, .6f };
	AddComponent(new ParticleEmitterComponent(L"Textures/Smoke.png", settings, 200));
}

void ParticleLifetime::Update(const SceneContext& sceneContext)
{
	m_Counter += sceneContext.pGameTime->GetElapsed();

	if (m_Counter >= m_LifeTime)
	{
		GetScene()->RemoveChild(this, true);
	}
}
