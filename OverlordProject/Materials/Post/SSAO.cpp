#include "stdafx.h"
#include "SSAO.h"

SSAO::SSAO()
	: PostProcessingMaterial(L"Effects/Post/SSAO.fx")
{
}

void SSAO::Draw(const SceneContext& sceneContext, RenderTarget* pSource)
{
	//Default Implementation > DrawPass with BaseEffect
	UpdateBaseEffectVariables(sceneContext, pSource); //Update Base Effect variables
	DrawPass(sceneContext, m_pBaseTechnique, m_pOutputTarget); //Draw with Base Technique to Output RT

	//Release Source SRV from pipeline
	constexpr ID3D11ShaderResourceView* const pSRV[] = { nullptr };
	sceneContext.d3dContext.pDeviceContext->PSSetShaderResources(0, 1, pSRV);
}

void SSAO::UpdateBaseEffectVariables(const SceneContext& , RenderTarget* pSource)
{

	m_pBaseEffect->GetVariableByName("gTexture")->AsShaderResource()->SetResource(pSource->GetDepthShaderResourceView());
}
