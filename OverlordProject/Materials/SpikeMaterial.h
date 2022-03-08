#pragma once

// SpikeMaterial Class									
class SpikeMaterial final : public Material<SpikeMaterial>
{
public:
	SpikeMaterial();				// Constructor
	~SpikeMaterial() override = default;				// Destructor

	// CopSpikeMaterial/move constructors and assignment operators
	SpikeMaterial(const SpikeMaterial& other) = delete;
	SpikeMaterial(SpikeMaterial&& other) noexcept = delete;
	SpikeMaterial& operator=(const SpikeMaterial& other) = delete;
	SpikeMaterial& operator=(SpikeMaterial&& other)	noexcept = delete;

protected:
	void InitializeEffectVariables() override;

};

