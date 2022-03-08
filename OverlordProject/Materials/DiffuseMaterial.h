#pragma once

// Include Files


// DiffuseMaterial Class									
class DiffuseMaterial final : public Material<DiffuseMaterial>
{
public:
	DiffuseMaterial();				// Constructor
	~DiffuseMaterial() override = default;				// Destructor

	// CopDiffuseMaterial/move constructors and assignment operators
	DiffuseMaterial(const DiffuseMaterial& other) = delete;
	DiffuseMaterial(DiffuseMaterial&& other) noexcept = delete;
	DiffuseMaterial& operator=(const DiffuseMaterial& other) = delete;
	DiffuseMaterial& operator=(DiffuseMaterial&& other)	noexcept = delete;

	// Member functions						
	void SetDiffuseTexture(const std::wstring& assetFile);

protected:
	void InitializeEffectVariables() override;

private:
	// Private member functions						

	// Datamembers								
	TextureData* m_pDiffuseTexture{};

};


