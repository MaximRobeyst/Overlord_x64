#include "stdafx.h"
#include "VertexAnimationMaterial.h"

VertexAnimationMaterial::VertexAnimationMaterial()
	: Material<VertexAnimationMaterial>(L"Effects/VertexAnimationTexture.fx")
{
}

void VertexAnimationMaterial::SetDiffuseTexture(const std::wstring& fileName)
{
	SetVariable_Texture(L"gDiffuseMap", ContentManager::Load<TextureData>(fileName));
}

void VertexAnimationMaterial::SetPositionTexture(const std::wstring& fileName)
{
	SetVariable_Texture(L"gPositionMap", ContentManager::Load<TextureData>(fileName));
}

void VertexAnimationMaterial::SetNormalTexture(const std::wstring& fileName)
{
	SetVariable_Texture(L"gNormalMap", ContentManager::Load<TextureData>(fileName));
}

void VertexAnimationMaterial::InitializeEffectVariables()
{
}
