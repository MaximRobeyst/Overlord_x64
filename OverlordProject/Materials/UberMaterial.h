#pragma once

// Include Files


// UberMaterial Class									
class UberMaterial final : public Material<UberMaterial>
{
public:
	UberMaterial();				// Constructor
	~UberMaterial() override = default;				// Destructor

	// CopUberMaterial/move constructors and assignment operators
	UberMaterial(const UberMaterial& other) = delete;
	UberMaterial(UberMaterial&& other) noexcept = delete;
	UberMaterial& operator=(const UberMaterial& other) = delete;
	UberMaterial& operator=(UberMaterial&& other)	noexcept = delete;

protected:
	void InitializeEffectVariables() override;

};


