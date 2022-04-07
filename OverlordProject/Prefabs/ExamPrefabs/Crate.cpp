#include "stdafx.h"
#include "Crate.h"

#include "Materials/DiffuseMaterial.h"

Crate::Crate()
{
}

void Crate::Initialize(const SceneContext&)
{
	auto model = AddComponent(new ModelComponent(L"Models/crate.ovm"));
	auto material = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	model->SetMaterial(material);
	
	material->SetDiffuseTexture(L"Textures/tex_crate.png");

	auto rigidbody = AddComponent(new RigidBodyComponent(true));

	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	rigidbody->AddCollider(PxBoxGeometry{ 0.25f, 0.25f, 0.25f }, *pDefaultMaterial, false, PxTransform{PxVec3{0.f, 0.25f, 0.f}});
}
