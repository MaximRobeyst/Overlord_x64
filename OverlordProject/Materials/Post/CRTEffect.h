#pragma once

class CRTEffect : public PostProcessingMaterial
{
public:
	CRTEffect();
	~CRTEffect() override = default;
	CRTEffect(const CRTEffect& other) = delete;
	CRTEffect(CRTEffect&& other) noexcept = delete;
	CRTEffect& operator=(const CRTEffect& other) = delete;
	CRTEffect& operator=(CRTEffect&& other) noexcept = delete;

	void DrawGui();
protected:
	void Initialize(const GameContext&) override {}

private:
	float m_LineOpacity1 = 1.25f;
	float m_LineOpacity2 = 0.1f;

	float m_Contrast = 2.1f;
	float m_Brighness = 1.f;
	float m_ScanColor = 0.25f;
	XMFLOAT2 m_Curvature{ 3.0f, 3.0f };

	float m_VignetteRoundness = 5.f;
	float m_VignetteOpacity = 2.5f;

};

