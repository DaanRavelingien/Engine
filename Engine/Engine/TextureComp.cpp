#include "EnginePCH.h"
#include "TextureComp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "TransformComp.h"

//static function
Component* TextureComp::CreateComp(const rapidjson::Value& args)
{
	TextureComp* pTextureComp{ nullptr };

	if (args.Empty())
		LOGERROR("Expected arguments for component of type: TEXTURECOMP");
	else
	{
		if (!args[0].IsString())
			LOGERROR("Expected different type of argument for component of type : TEXTURECOMP");
		else
			pTextureComp = new TextureComp{ args[0].GetString() };
	}

	return pTextureComp;
}

TextureComp::TextureComp(const std::string& file)
	:Component(typeid(this).name())
	, m_FilePath{file}
	, m_TextureIdx{ -1 }
{
	//creating our texture on the resource manager so we dont need to take ownership of it
	m_TextureIdx = ResourceManager::GetInstance().LoadTexture(m_FilePath);

	//setting the default source rectangle to the size of the whole texture
	m_SourceRect = glm::vec4{ 0,0,
	ResourceManager::GetInstance().GetResource<Texture2D>(m_TextureIdx)->GetTextureSize().x,
	ResourceManager::GetInstance().GetResource<Texture2D>(m_TextureIdx)->GetTextureSize().y };

	//setting the destination rectangle to the same size as well
	m_DestRect = m_SourceRect;
}

void TextureComp::Initialize()
{
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}

void TextureComp::ChangeTexture(const std::string& file)
{
	m_TextureIdx = ResourceManager::GetInstance().ReplaceTexture(m_TextureIdx, file);

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}

glm::vec4 TextureComp::GetDestRect() const
{
	glm::vec4 rect{ m_DestRect };

	rect.x += m_pGameObj->GetTransform()->GetPos().x;
	rect.y += m_pGameObj->GetTransform()->GetPos().y;
	rect.z *= m_pGameObj->GetTransform()->GetScale().x;
	rect.w *= m_pGameObj->GetTransform()->GetScale().y;

	return rect;
}
