#include "EnginePCH.h"
#include "TextureComp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"

TextureComp::TextureComp(const std::string& filePath)
	:m_FilePath{filePath}
	, m_pTexture{ nullptr }
{
	//creating our texture on the resource manager so we dont need to take ownership of it
	m_pTexture = ResourceManager::GetInstance().LoadTexture(m_FilePath);
}

void TextureComp::Initialize()
{
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}

void TextureComp::ChangeTexture(const std::string& filePath)
{
	//deleting the old texture
	delete m_pTexture;
	m_pTexture = nullptr;

	//swapping out for the new texture
	m_FilePath = filePath;
	m_pTexture = new Texture2D{ filePath };

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}
