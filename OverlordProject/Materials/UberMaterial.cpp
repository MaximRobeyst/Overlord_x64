#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial()
	: Material<UberMaterial>(L"Effects/UberShader.fx")
{
}

void UberMaterial::InitializeEffectVariables()
{
	SetVariable_Vector(L"gColorDiffuse", XMFLOAT4{ 1,0,0,1 });
	SetVariable_Scalar(L"gUseTextureDiffuse", true);
	SetVariable_Texture(L"gTextureDiffuse", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Diffusemap.tga"));

	SetVariable_Vector(L"gColorSpecular", XMFLOAT4{ 0,1.f, 0.79f, 1.f });
	SetVariable_Scalar(L"gUseTextureSpecularIntensity", true);
	SetVariable_Texture(L"gTextureSpecularIntensity", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Heightmap.tga"));
	SetVariable_Scalar(L"gShininess", 40);

	SetVariable_Scalar(L"gFlipGreenChannel", true);
	SetVariable_Scalar(L"gUseTextureNormal", true);
	SetVariable_Texture(L"gTextureNormal", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Normalmap.tga"));
	SetVariable_Scalar(L"gUseEnvironmentMapping", true);
	SetVariable_Scalar(L"gReflectionStrength", 0.8f);
	SetVariable_Scalar(L"gRefractionStrength", 0.5f);
	SetVariable_Scalar(L"gRefractionIndex", 0.9f);
	
	SetVariable_Scalar(L"gUseFresnelFalloff", true);
	SetVariable_Scalar(L"gFresnelPower", 2.f);
	SetVariable_Scalar(L"gFresnelMultiplier", 1.5f);
	SetVariable_Scalar(L"gFresnelHardness", 2.0f);



	SetVariable_Scalar(L"gUseSpecularPhong", true);

	SetVariable_Texture(L"gCubeEnvironment", ContentManager::Load<TextureData>(L"Textures/Sunol_Cubemap.dds"));


	SetVariable_Scalar(L"gReflectionStrength", 0.5f);

}
