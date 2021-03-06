#include "stdafx.h"
#include "BoneObject.h"

BoneObject::BoneObject(BaseMaterial* pMaterial, float length)
	: m_Length{length}
	, m_pMaterial{pMaterial}
{
}

void BoneObject::AddBone(BoneObject* pBone)
{
	pBone->GetTransform()->Translate(m_Length, 0.f, 0.f);
	this->AddChild(pBone);
}

void BoneObject::CalculateBindPose()
{
	auto matrix = XMLoadFloat4x4(&GetTransform()->GetWorld());
	XMMatrixInverse(nullptr, matrix);
	XMStoreFloat4x4(&m_BindPose, matrix);

	for (auto p : this->GetChildren<BoneObject>())
	{
		p->CalculateBindPose();
	}
}

void BoneObject::Initialize(const SceneContext&)
{
	GameObject* pEmpty = new GameObject();
	AddChild(pEmpty);
	auto pModel = pEmpty->AddComponent(new ModelComponent(L"Models/Bone.ovm"));
	pModel->SetMaterial(m_pMaterial);
	pEmpty->GetTransform()->Rotate(0.f, -90.f, 0.f, true);
	pEmpty->GetTransform()->Scale(m_Length);
}


