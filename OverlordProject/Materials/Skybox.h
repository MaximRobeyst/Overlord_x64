#pragma once
class Skybox final : public Material<Skybox>
{
public:
	Skybox();				// Constructor
	~Skybox() override = default;				// Destructor

	// CopSkybox/move constructors and assignment operators
	Skybox(const Skybox & other) = delete;
	Skybox(Skybox && other) noexcept = delete;
	Skybox& operator=(const Skybox & other) = delete;
	Skybox& operator=(Skybox && other)	noexcept = delete;

	void SetSkyboxTexture(const std::wstring& assetFile);

protected:
	void InitializeEffectVariables() override;

private:
	TextureData* m_pCubeTexture{};
};

