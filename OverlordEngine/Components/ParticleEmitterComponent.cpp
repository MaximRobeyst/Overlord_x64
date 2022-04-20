#include "stdafx.h"
#include "ParticleEmitterComponent.h"
#include "Misc/ParticleMaterial.h"

ParticleMaterial* ParticleEmitterComponent::m_pParticleMaterial{};

ParticleEmitterComponent::ParticleEmitterComponent(const std::wstring& assetFile, const ParticleEmitterSettings& emitterSettings, UINT particleCount):
	m_ParticlesArray(new Particle[particleCount]),
	m_ParticleCount(particleCount), //How big is our particle buffer?
	m_MaxParticles(particleCount), //How many particles to draw (max == particleCount)
	m_AssetFile(assetFile),
	m_EmitterSettings(emitterSettings)
{
	m_enablePostDraw = true; //This enables the PostDraw function for the component
}

ParticleEmitterComponent::~ParticleEmitterComponent()
{
	delete m_ParticlesArray;
	m_pVertexBuffer->Release();
}

void ParticleEmitterComponent::Initialize(const SceneContext& sceneContext)
{
	m_pParticleMaterial = MaterialManager::Get()->GetMaterial<ParticleMaterial>(0);
	CreateVertexBuffer(sceneContext);
	m_pParticleTexture = ContentManager::Load<TextureData>(m_AssetFile);
}

void ParticleEmitterComponent::CreateVertexBuffer(const SceneContext& sceneContext)
{
	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();

	D3D11_BUFFER_DESC vertexBufferDesc{};
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexParticle) * m_ParticleCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	HANDLE_ERROR(sceneContext.d3dContext.pDevice->CreateBuffer(&vertexBufferDesc, nullptr, &m_pVertexBuffer))

}

void ParticleEmitterComponent::Update(const SceneContext& sceneContext)
{
	float particleInterval = ((m_EmitterSettings.maxEnergy + m_EmitterSettings.minEnergy) / 2) / m_MaxParticles;
	m_LastParticleSpawn += sceneContext.pGameTime->GetElapsed();
	m_ActiveParticles = 0;
	VertexParticle* pBuffer{ nullptr };
	D3D11_MAPPED_SUBRESOURCE* pData = reinterpret_cast<D3D11_MAPPED_SUBRESOURCE*>(pBuffer);
	sceneContext.d3dContext.pDeviceContext->Map(m_pVertexBuffer, 1, D3D11_MAP_WRITE_DISCARD, 0, pData);
	for (auto i = 0; i < m_ParticleCount; ++i)
	{
		auto currentParticle = m_ParticlesArray[i];

		if (currentParticle.isActive)
			UpdateParticle(currentParticle, sceneContext.pGameTime->GetElapsed());
		if (!currentParticle.isActive && m_LastParticleSpawn >= particleInterval)
			SpawnParticle(currentParticle);
	}
}

void ParticleEmitterComponent::UpdateParticle(Particle& /*p*/, float /*elapsedTime*/) const
{
	TODO_W9(L"Implement UpdateParticle")
}

void ParticleEmitterComponent::SpawnParticle(Particle& /*p*/)
{
	TODO_W9(L"Implement SpawnParticle")
}

void ParticleEmitterComponent::PostDraw(const SceneContext& /*sceneContext*/)
{
	TODO_W9(L"Implement PostDraw")
}

void ParticleEmitterComponent::DrawImGui()
{
	if(ImGui::CollapsingHeader("Particle System"))
	{
		ImGui::SliderUInt("Count", &m_ParticleCount, 0, m_MaxParticles);
		ImGui::InputFloatRange("Energy Bounds", &m_EmitterSettings.minEnergy, &m_EmitterSettings.maxEnergy);
		ImGui::InputFloatRange("Size Bounds", &m_EmitterSettings.minSize, &m_EmitterSettings.maxSize);
		ImGui::InputFloatRange("Scale Bounds", &m_EmitterSettings.minScale, &m_EmitterSettings.maxScale);
		ImGui::InputFloatRange("Radius Bounds", &m_EmitterSettings.minEmitterRadius, &m_EmitterSettings.maxEmitterRadius);
		ImGui::InputFloat3("Velocity", &m_EmitterSettings.velocity.x);
		ImGui::ColorEdit4("Color", &m_EmitterSettings.color.x, ImGuiColorEditFlags_NoInputs);
	}
}