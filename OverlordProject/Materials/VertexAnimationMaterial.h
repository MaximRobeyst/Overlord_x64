#pragma once
class VertexAnimationMaterial final : public Material<VertexAnimationMaterial>
{
public:
	VertexAnimationMaterial();
	~VertexAnimationMaterial() override = default;

	VertexAnimationMaterial(const VertexAnimationMaterial& other) = delete;
	VertexAnimationMaterial(VertexAnimationMaterial&& other) noexcept = delete;
	VertexAnimationMaterial& operator=(const VertexAnimationMaterial& other) = delete;
	VertexAnimationMaterial& operator=(VertexAnimationMaterial&& other)	noexcept = delete;

	void SetDiffuseTexture(const std::wstring& fileName);
	void SetPositionTexture(const std::wstring& fileName);
	void SetNormalTexture(const std::wstring& fileName);

protected:

	void InitializeEffectVariables() override;
};