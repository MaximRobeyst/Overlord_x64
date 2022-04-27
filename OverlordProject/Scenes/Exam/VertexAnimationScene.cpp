#include "stdafx.h"
#include "VertexAnimationScene.h"
#include <Materials/DiffuseMaterial.h>

void VertexAnimationScene::Initialize()
{
	GetSceneSettings().enableOnGUI = true;

	m_pCrate = AddChild(new GameObject());
	const auto pModel = m_pCrate->AddComponent(new ModelComponent(L"Meshes/Crate.ovm"));

	m_pColorMaterial = MaterialManager::Get()->CreateMaterial<VertexAnimationMaterial>();
	m_pColorMaterial->SetDiffuseTexture(L"Textures/tex_Crate.png");
	m_pColorMaterial->SetPositionTexture(L"Textures/offsets.png");

	m_pColorMaterial->SetVariable_Scalar(L"gTextureWidth", 106);

	pModel->SetMaterial(m_pColorMaterial);

	m_pCrate->GetTransform()->Scale(0.1f);
}

void VertexAnimationScene::Update()
{
	//scaleFactor *= scaleFactor * m_SceneContext.pGameTime->GetElapsed();
	//m_pCrate->GetTransform()->Scale(scaleFactor);

	m_CurrentFrame += m_SceneContext.pGameTime->GetElapsed();
	m_CurrentFrame = fmodf(m_CurrentFrame, 30.f);
	m_pColorMaterial->SetVariable_Scalar(L"gCurrentFrame", m_CurrentFrame);
}

void VertexAnimationScene::Draw()
{
}

void VertexAnimationScene::OnGUI()
{
	ImGui::Text(std::to_string(m_CurrentFrame).c_str());
}
