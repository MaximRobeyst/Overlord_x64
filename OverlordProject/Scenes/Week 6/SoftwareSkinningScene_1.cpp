#include "stdafx.h"
#include "SoftwareSkinningScene_1.h"
#include <Materials/ColorMaterial.h>
#include "Prefabs/BoneObject.h"

void SoftwareSkinningScene_1::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	ColorMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	auto pRoot = new GameObject();
	m_pBone0 = new BoneObject(pMaterial, 15.0f );
	pRoot->AddChild(m_pBone0);
	m_pBone1 = new BoneObject(pMaterial, 15.0f);
	m_pBone0->AddBone(m_pBone1);

	AddChild(pRoot);
}

void SoftwareSkinningScene_1::Update()
{
	if (!m_AutoRotate)
		return;

	m_BoneRotation += m_RotationSign * m_RotationSpeed * GetSceneContext().pGameTime->GetElapsed();
	if (m_BoneRotation >= m_MaxAngle || m_BoneRotation <= -m_MaxAngle)
		m_RotationSign *= -1;

	m_pBone0->GetTransform()->Rotate(0.f, 0.f, m_BoneRotation, true);
	m_pBone1->GetTransform()->Rotate(0.f, 0.f, -m_BoneRotation * 2.f, true);

}

void SoftwareSkinningScene_1::OnGUI()
{
	ImGui::Checkbox("Auto Rotate", &m_AutoRotate);

	if (ImGui::DragFloat3("Bone 0 : ROT", m_Bone0Rotation, 1.f, 0.0f, 360.f))
	{
		m_pBone0->GetTransform()->Rotate(v[0], v[1], v[2], true);
	}
}
