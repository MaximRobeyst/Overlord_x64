#pragma once
class Crate : public GameObject
{
public:
	Crate();
	~Crate() override = default;

	Crate(const Crate & other) = delete;
	Crate(Crate && other) noexcept = delete;
	Crate& operator=(const Crate & other) = delete;
	Crate& operator=(Crate && other) noexcept = delete;

protected:
	void Initialize(const SceneContext&) override;
};

