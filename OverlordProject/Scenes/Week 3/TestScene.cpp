#include "stdafx.h"
#include "TestScene.h"

#include "Prefabs/SpherePrefab.h"

void TestScene::Initialize()
{
	auto pDefaultMaterial = PxGetPhysics().createMaterial(.5f, .5f, 1.f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	//Sphere 1 (Group 1)
	auto pSphereObject = AddChild(new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Red }));
	auto pSphereActor = pSphereObject->AddComponent(new RigidBodyComponent());
	pSphereActor->AddCollider(PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	pSphereObject->GetTransform()->Translate (0.f, 50.f, 0.f);

	pSphereActor->SetCollisionGroup(CollisionGroup::Group1);

	//Sphere 2 (Group 0)
	pSphereObject = AddChild(new SpherePrefab(1.f, 10, XMFLOAT4{Colors::Blue}));
	pSphereActor = pSphereObject->AddComponent(new RigidBodyComponent());
	pSphereActor->AddCollider(PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	pSphereObject->GetTransform()->Translate(0.f, 40.f, 0.f);

	pSphereActor->SetCollisionIgnoreGroups(CollisionGroup::Group1);

	//Sphere 2 (Group 0)
	pSphereObject = AddChild(new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Green }));
	pSphereActor = pSphereObject->AddComponent(new RigidBodyComponent());
	pSphereActor->AddCollider(PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	pSphereObject->GetTransform()->Translate(0.f, 30.f, 0.f);
}
