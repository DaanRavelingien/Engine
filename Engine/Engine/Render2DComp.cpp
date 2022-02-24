#include "EnginePCH.h"
#include "Render2DComp.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TextComp.h"
#include "TransformComp.h"
#include "TextureComp.h"

Render2DComp::Render2DComp()
	:Component(typeid(this).name())
{
}

void Render2DComp::Render()
{
	for (std::pair<Component*, int> pair : m_CompsToRender)
	{
		//check if the texture is something
		if (pair.second >= 0)
		{
			const auto& pos = m_pGameObj->GetTransform()->GetPos();
			Renderer::GetInstance().RenderTexture(
				*ResourceManager::GetInstance().GetResource<Texture2D>(pair.second),
				pos.x, pos.y);
		}
		else
		{
			LOGWARNING("the resource idx was invalid");
		}
	}
}

int Render2DComp::MakeTextureFromText(const glm::vec3& color, int fontIdx, const std::string& text)
{
	const SDL_Color sdlColor = { Uint8(color.r * 255),Uint8(color.g * 255),Uint8(color.b * 255) };
	const auto surf = TTF_RenderText_Blended(
		ResourceManager::GetInstance().GetResource<Font>(fontIdx)->GetFont(),
		text.c_str(), sdlColor);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	return ResourceManager::GetInstance().LoadTexture(texture);
}

void Render2DComp::AddTextureToRender(Component* pComp, int textureIdx)
{
	//first we do a check if its already in the vector 
	auto it = std::find_if(m_CompsToRender.begin(), m_CompsToRender.end(), [pComp](const std::pair<Component*, int>& pair)
		{
			if (pair.first == pComp)
				return true;
			return false;
		});

	int newTextureIdx{ textureIdx };

	//if its already in there do not add the component again, just change the texture
	if (it != m_CompsToRender.end())
	{
		newTextureIdx = ResourceManager::GetInstance().ReplaceResource(it->second, textureIdx);
	}

	//else add it to the vector
	m_CompsToRender.push_back({ pComp,newTextureIdx });
}

void Render2DComp::Notify(Component* pComp, Event event)
{
	TextComp* pTextComp{nullptr};
	int textureIdx{ 0 };
	TextureComp* pTextureComp{ nullptr };

	switch (event)
	{
	case Event::COMPONENT_TEXT_RENDER:
		pTextComp = m_pGameObj->GetComponent<TextComp>(pComp->GetIdx());
		textureIdx = MakeTextureFromText(pTextComp->GetColor(), pTextComp->GetFontIdx(), pTextComp->GetText());
		AddTextureToRender(pComp, textureIdx);
		break;

	case Event::COMPONENT_TEXTURE_RENDER:
		pTextureComp = m_pGameObj->GetComponent<TextureComp>(pComp->GetIdx());
		AddTextureToRender(pComp, pTextureComp->GetTextureIdx());
		break;

	default:
		break;
	}
}
