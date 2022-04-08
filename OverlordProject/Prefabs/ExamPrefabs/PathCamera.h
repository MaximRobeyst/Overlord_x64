#pragma once
class PathCamera final : public GameObject
{
public:
	PathCamera(TransformComponent* followTarget, const std::vector<XMFLOAT3>& m_Path);
	~PathCamera() override = default;
	PathCamera(const PathCamera & other) = delete;
	PathCamera(PathCamera && other) noexcept = delete;
	PathCamera& operator=(const PathCamera & other) = delete;
	PathCamera& operator=(PathCamera && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void Draw(const SceneContext& sceneContext) override;

private:
	std::vector<XMFLOAT3> m_Path{};
	TransformComponent* m_pFollowTarget{};
	CameraComponent* m_pCamera{};

	int m_CurrentIndex{ 0 };
};

