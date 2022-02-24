#include "EnginePCH.h"
#include "TextureComp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"

TextureComp::TextureComp(const std::string& file)
	:Component(typeid(this).name())
	, m_FilePath{file}
	, m_TextureIdx{ -1 }
{
	//creating our texture on the resource manager so we dont need to take ownership of it
	m_TextureIdx = ResourceManager::GetInstance().LoadTexture(m_FilePath);
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
