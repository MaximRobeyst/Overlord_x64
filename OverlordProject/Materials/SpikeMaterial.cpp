#include "stdafx.h"
#include "SpikeMaterial.h"

SpikeMaterial::SpikeMaterial()
	: Material<SpikeMaterial>(L"Effects/SpikyShader.fx")
{
}

void SpikeMaterial::InitializeEffectVariables()
{
	SetVariable_Scalar(L"gSpikeLength", 0.2f);
}
