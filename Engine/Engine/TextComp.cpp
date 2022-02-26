#include "EnginePCH.h"
#include "TextComp.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"
#include "TransformComp.h"

TextComp::TextComp(const std::string& text, const std::string& file, unsigned int fontSize, const glm::vec3& color)
	: Component(typeid(this).name())
	, m_Text{text}
	, m_FontIdx{-1}
	, m_FontFile{file}
	, m_Color{color}
	, m_FontSize{fontSize}
{
	//creating our font on the resource manager so we dont need to take ownership of it
	m_FontIdx = ResourceManager::GetInstance().LoadFont(m_FontFile, m_FontSize);
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

void TextComp::SetFont(const std::string& file)
{
	m_FontIdx = ResourceManager::GetInstance().ReplaceFont(m_FontIdx, file, m_FontSize);
	m_FontFile = file;
	
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

void TextComp::SetFontSize(unsigned int fontSize)
{
	m_FontIdx = ResourceManager::GetInstance().ReplaceFont(m_FontIdx, m_FontFile, fontSize);
	m_FontSize = fontSize;

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXT_RENDER);
}

unsigned int TextComp::GetFontSize() const
{
	unsigned int size{ m_FontSize };
	//taking into account the scale of the game obj
	size *= unsigned int(m_pGameObj->GetTransform()->GetScale().x);

	return size;
}
