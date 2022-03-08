#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial()
	: Material<UberMaterial>(L"Effects/UberShader.fx")
{
}

void UberMaterial::InitializeEffectVariables()
{
	SetVariable_Scalar(L"gUseTextureDiffuse", true);
	SetVariable_Texture(L"gTextureDiffuse", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Diffusemap.tga"));

	SetVariable_Scalar(L"gUseTextureNormal", true);
	SetVariable_Texture(L"gTextureNormal", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Normalmap.tga"));

	SetVariable_Scalar(L"gUseSpecularBlinn", true);
	SetVariable_Scalar(L"gUseSpecularPhong", true);
}
