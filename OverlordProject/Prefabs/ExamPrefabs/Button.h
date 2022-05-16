#pragma once
class Button : public GameObject
{
public:
	Button();
	~Button() override = default;

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

protected:

};

