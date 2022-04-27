#pragma once
#include <Materials/VertexAnimationMaterial.h>
class VertexAnimationScene final : public GameScene
{
public:
	VertexAnimationScene() : GameScene(L"VertexAnimationScene") {};
	~VertexAnimationScene() override = default;

	VertexAnimationScene(const VertexAnimationScene& other) = delete;
	VertexAnimationScene(VertexAnimationScene&& other) noexcept = delete;
	VertexAnimationScene& operator=(const VertexAnimationScene& other) = delete;
	VertexAnimationScene& operator=(VertexAnimationScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	VertexAnimationMaterial* m_pColorMaterial;
	GameObject* m_pCrate;

	//float scaleFactor = 2.0f;
	float m_CurrentFrame = 0.0f;
};


