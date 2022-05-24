#include "stdafx.h"
#include "Skybox.h"

Skybox::Skybox()
	:Material<Skybox>(L"Effects/Skybox.fx")
{
}

void Skybox::SetSkyboxTexture(const std::wstring& assetFile)
{
	SetVariable_Texture(L"gCubeTexture", ContentManager::Load<TextureData>(assetFile));
}

void Skybox::InitializeEffectVariables()
{
	SetVariable_Texture(L"gCubeTexture", ContentManager::Load<TextureData>(L"Textures/Sunol_Cubemap.dds"));
}
