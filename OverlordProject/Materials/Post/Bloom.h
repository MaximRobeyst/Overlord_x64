#pragma once

class Bloom : public PostProcessingMaterial
{
public:
	Bloom();
	~Bloom() override = default;
	Bloom(const Bloom& other) = delete;
	Bloom(Bloom&& other) noexcept = delete;
	Bloom& operator=(const Bloom& other) = delete;
	Bloom& operator=(Bloom&& other) noexcept = delete;

	void DrawGui();
protected:
	void Initialize(const GameContext&) override {}

private:
	float m_LineOpacity1 = 1.25f;
	float m_LineOpacity2 = 0.1f;

	float m_Contrast = 2.1f;
	float m_Brighness = 1.f;
	float m_ScanColor = 0.25f;

};

