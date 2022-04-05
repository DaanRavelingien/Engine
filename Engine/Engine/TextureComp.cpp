#include "EnginePCH.h"
#include "TextureComp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "TransformComp.h"

TextureComp::TextureComp(const std::string& textureName)
	:Component{ typeid(this).name() }
	, m_TextureName{textureName}
{
	//setting the default source rectangle to the size of the whole texture
	m_SourceRect = glm::vec4{ 0,0,
	ResourceManager::GetInstance().GetResource<Texture2D>(m_TextureName)->GetTextureSize().x,
	ResourceManager::GetInstance().GetResource<Texture2D>(m_TextureName)->GetTextureSize().y };

	//setting the destination rectangle to the same size as well
	m_DestRect = m_SourceRect;
}

void TextureComp::Initialize()
{
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}

void TextureComp::ChangeTexture(const std::string& newTextureName)
{
	m_TextureName = newTextureName;
	m_pGameObj->SendNotification(this, Event::COMPONENT_TEXTURE_RENDER);
}

glm::vec4 TextureComp::GetDestRect() const
{
	glm::vec4 rect{ m_DestRect };

	rect.x *= m_pGameObj->GetTransform()->GetScale().x;
	rect.y *= m_pGameObj->GetTransform()->GetScale().y;
	rect.x += m_pGameObj->GetTransform()->GetPos().x;
	rect.y += m_pGameObj->GetTransform()->GetPos().y;

	rect.z *= m_pGameObj->GetTransform()->GetScale().x;
	rect.w *= m_pGameObj->GetTransform()->GetScale().y;

	return rect;
}
