#include "stdafx.h"
#include "Bloom.h"

Bloom::Bloom()
	: PostProcessingMaterial(L"Effects/Post/Bloom.fx")
{
}

void Bloom::DrawGui()
{
	if(ImGui::InputFloat("Fill color 1", &m_LineOpacity1))
		m_pBaseEffect->GetVariableByName("gLineOpacity1")->AsScalar()->SetFloat(m_LineOpacity1);

	if(ImGui::InputFloat("Fill color 2", &m_LineOpacity2))
		m_pBaseEffect->GetVariableByName("gLineOpacity2")->AsScalar()->SetFloat(m_LineOpacity2);

	if (ImGui::InputFloat("Brightness", &m_Brighness))
		m_pBaseEffect->GetVariableByName("gBrightness")->AsScalar()->SetFloat(m_Brighness);
}
