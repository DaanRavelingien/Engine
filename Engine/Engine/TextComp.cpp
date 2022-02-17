#include "EnginePCH.h"
#include "TextComp.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"

TextComp::TextComp(const std::string& text, const std::string& fontFilePath, int fontSize)
	: m_Text{text}
	, m_pFont{nullptr}
	, m_FontFilePath{fontFilePath}
	, m_Color{1,1,1}
	, m_FontSize{fontSize}
{
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontFilePath, m_FontSize);

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

TextComp::~TextComp()
{
	delete m_pFont;
	m_pFont = nullptr;
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

void TextComp::SetFont(const std::string& fontFilePath)
{
	//safly deleting the old font
	delete m_pFont; 
	m_pFont = nullptr; 

	//setting the new font
	m_FontFilePath = fontFilePath;
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontFilePath, m_FontSize);
	
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

void TextComp::SetFontSize(int fontSize)
{
	//safly deleting the old font
	delete m_pFont;
	m_pFont = nullptr;

	//creating the new font with the new size
	m_FontSize = fontSize;
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontFilePath, m_FontSize);

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}
