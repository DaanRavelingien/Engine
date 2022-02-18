#include "EnginePCH.h"
#include "TextComp.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"

TextComp::TextComp(const std::string& text, const std::string& fontFilePath, unsigned int fontSize, const glm::vec3& color)
	: m_Text{text}
	, m_pFont{nullptr}
	, m_FontFilePath{fontFilePath}
	, m_Color{color}
	, m_FontSize{fontSize}
{
	//creating our font on the resource manager so we dont need to take ownership of it
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontFilePath, m_FontSize);
}

void TextComp::Initialize()
{
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

void TextComp::SetFont(const std::string& fontFilePath)
{
	//deleting the old font
	delete m_pFont; 
	m_pFont = nullptr; 

	//swapping out for the new font
	m_FontFilePath = fontFilePath;
	m_pFont = new Font{m_FontFilePath,m_FontSize};
	
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

void TextComp::SetFontSize(unsigned int fontSize)
{
	//safly deleting the old font
	delete m_pFont;
	m_pFont = nullptr;

	//swapping out for the new font
	m_FontSize = fontSize;
	m_pFont = new Font{ m_FontFilePath,m_FontSize };

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}
