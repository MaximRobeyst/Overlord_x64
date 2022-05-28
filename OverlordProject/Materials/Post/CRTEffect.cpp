#include "stdafx.h"
#include "CRTEffect.h"

CRTEffect::CRTEffect()
	: PostProcessingMaterial(L"Effects/Post/CRTEffect.fx")
{
}

void CRTEffect::DrawGui()
{
	if(ImGui::InputFloat("Fill color 1", &m_LineOpacity1))
		m_pBaseEffect->GetVariableByName("gLineOpacity1")->AsScalar()->SetFloat(m_LineOpacity1);

	if(ImGui::InputFloat("Fill color 2", &m_LineOpacity2))
		m_pBaseEffect->GetVariableByName("gLineOpacity2")->AsScalar()->SetFloat(m_LineOpacity2);

	if (ImGui::InputFloat("Brightness", &m_Brighness))
		m_pBaseEffect->GetVariableByName("gBrightness")->AsScalar()->SetFloat(m_Brighness);

	float curvature[2] = {m_Curvature.x, m_Curvature.y};
	if (ImGui::InputFloat2("Curvature ", curvature))
	{
		m_Curvature.x = curvature[0];
		m_Curvature.y = curvature[1];
		m_pBaseEffect->GetVariableByName("gCurvature")->AsVector()->SetFloatVector(curvature);
	}

	if (ImGui::InputFloat("VignetteRoundness", &m_VignetteRoundness))
		m_pBaseEffect->GetVariableByName("gVignetteRoundness")->AsScalar()->SetFloat(m_VignetteRoundness);

	if (ImGui::InputFloat("VignetteOpacity", &m_VignetteOpacity))
		m_pBaseEffect->GetVariableByName("gVignetteOpacity")->AsScalar()->SetFloat(m_VignetteOpacity);
}
