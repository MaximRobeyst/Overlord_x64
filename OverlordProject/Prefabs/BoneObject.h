#pragma once
class BoneObject final :public GameObject
{
public:
	BoneObject(BaseMaterial* pMaterial, float length = 5.f);
	~BoneObject() override = default;
	BoneObject(const BoneObject& other) = delete;
	BoneObject(const BoneObject&& other) noexcept = delete;
	BoneObject& operator= (const BoneObject & other) = delete;
	BoneObject& operator= (BoneObject && other) noexcept = delete;


	//Part_2 [ADDED]
	const XMFLOAT4X4& GetBindPose() const { return m_BindPose; }
	void AddBone(BoneObject* pBone);
protected:
	void Initialize(const SceneContext&) override;

private:
	float m_Length{};
	BaseMaterial* m_pMaterial{};

	//Part_2 {ADDED]
	XMFLOAT4X4 m_BindPose{};
};
