#pragma once
class SSAO : public PostProcessingMaterial
{
public:
	SSAO();
	~SSAO() override = default;
	SSAO(const SSAO & other) = delete;
	SSAO(SSAO && other) noexcept = delete;
	SSAO& operator=(const SSAO & other) = delete;
	SSAO& operator=(SSAO && other) noexcept = delete;

	void Draw(const SceneContext& sceneContext, RenderTarget* pSource) override;

protected:
	void Initialize(const GameContext&) override {}
	void UpdateBaseEffectVariables(const SceneContext& sceneContext, RenderTarget* pSource);

};

