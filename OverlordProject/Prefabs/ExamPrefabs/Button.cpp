#include "stdafx.h"
#include "Button.h"

Button::Button(std::wstring text, XMFLOAT2 position, XMFLOAT4 color, XMFLOAT2 bounds)
	: m_Text{text}
	, m_Position{position}
	, m_Color{color}
	, m_Bounds{bounds}
	, m_pFont{ ContentManager::Load<SpriteFont>(L"SpriteFonts/CrashALike_64.fnt") }
{
}

void Button::SetOnClickFunction(std::function<void()> newClickFunction)
{
	m_OnClickFunction = newClickFunction;
}

void Button::Draw(const SceneContext& sceneContext)
{
	DebugRenderer::DrawLine(XMFLOAT3{m_Position.x, m_Position.y, 0.f}, XMFLOAT3{m_Position.x + m_Bounds.x, m_Position.y ,0});

	if (!IsOverrlapping(sceneContext))
	{
		TextRenderer::Get()->DrawText(m_pFont, m_Text, m_Position, m_Color);
		return;
	}

	TextRenderer::Get()->DrawText(m_pFont, m_Text, m_Position, XMFLOAT4{ Colors::Red });
	if (sceneContext.pInput->IsMouseButton(InputState::pressed, VK_LBUTTON) && m_OnClickFunction != nullptr)
		m_OnClickFunction();
}

void Button::Update(const SceneContext&)
{
}

bool Button::IsOverrlapping(const SceneContext& sceneContext)
{
	auto mousePos = sceneContext.pInput->GetMousePosition();

	if (mousePos.x > m_Position.x && mousePos.x < m_Position.x + m_Bounds.x
		&& mousePos.y > m_Position.y && mousePos.y < m_Position.y + m_Bounds.y)
	{
		return true;
	}

	return false;
}
