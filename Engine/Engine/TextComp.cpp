#include "EnginePCH.h"
#include "TextComp.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"
#include "TransformComp.h"

TextComp::TextComp(const std::string& text, const std::string& fontName, const glm::vec3& color)
	: Component(typeid(this).name())
	, m_Text{text}
	, m_FontName{fontName}
	, m_Color{color}
{}

void TextComp::Initialize()
{
	m_pGameObj->SendNotification(this, Event::TEXT_RENDER);
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;

	m_pGameObj->SendNotification(this, Event::TEXT_RENDER);
}

void TextComp::SetFont(const std::string& newFontName)
{
	m_FontName = newFontName;
	m_pGameObj->SendNotification(this, Event::TEXT_RENDER);
}

unsigned int TextComp::GetFontSize() const
{
	return ResourceManager::GetInstance().GetResource<Font>(m_FontName)->GetFontSize();
}
