#pragma once
class PathCamera final : public GameObject
{
public:
	PathCamera(TransformComponent* followTarget, const XMFLOAT3& offset = XMFLOAT3{});
	~PathCamera() override;
	PathCamera(const PathCamera & other) = delete;
	PathCamera(PathCamera && other) noexcept = delete;
	PathCamera& operator=(const PathCamera & other) = delete;
	PathCamera& operator=(PathCamera && other) noexcept = delete;

	void DrawImGui();
	void ResetCamera();

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void Draw(const SceneContext& sceneContext) override;

private:
	struct PathPoint {
		XMFLOAT3 point;
		XMFLOAT3 rotation;
	};

	std::vector<PathPoint> m_Path{};
	XMFLOAT3 m_Offset{};

	TransformComponent* m_pFollowTarget{};
	CameraComponent* m_pCamera{};

	int m_CurrentIndex{ 1 };
	float m_Percentage{ 0.0f };
	bool m_Save{ true };
};

