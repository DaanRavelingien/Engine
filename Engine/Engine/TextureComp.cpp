#include "EnginePCH.h"
#include "TextureComp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"

TextureComp::TextureComp(const std::string& filePath)
	:m_FilePath{filePath}
	, m_pTexture{ nullptr }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(m_FilePath);
}

TextureComp::~TextureComp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void TextureComp::Initialize()
{
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}

void TextureComp::ChangeTexture(const std::string& filePath)
{
	delete m_pTexture;
	m_pTexture = nullptr;

	m_FilePath = filePath;
	m_pTexture = ResourceManager::GetInstance().LoadTexture(m_FilePath);

	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}
