#include "EnginePCH.h"
#include "TextComp.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"
#include "TransformComp.h"

//static function
Component* TextComp::CreateComp(const rapidjson::Value& args)
{
	TextComp* pTextComp{ nullptr };

	if (args.Empty())
		LOGERROR("Expected arguments for component of type: TEXTCOMP");
	else
	{
		if (!args[0].IsString() || !args[1].IsString() || !args[2].IsInt() || !args[3].IsArray())
			LOGERROR("Expected different type of argument for component of type : TEXTCOMP");
		else
		{
			pTextComp = new TextComp{ args[0].GetString(), args[1].GetString(), unsigned int(args[2].GetInt())
				, {args[3][0].GetFloat(),args[3][1].GetFloat(),args[3][2].GetFloat()} };
		}
	}

	return pTextComp;
}

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
