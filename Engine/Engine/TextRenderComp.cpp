#include "EnginePCH.h"
#include "TextRenderComp.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "Texture2D.h"
#include "Scene.h"

//component includes
#include "TransformComp.h"
#include "TextComp.h"

TextRenderComp::TextRenderComp()
	:Component{typeid(this).name()}
{
}

void TextRenderComp::Initialize()
{
	//subscibing the renderComp to the game object
	m_pGameObj->AddObserver(this);
}

void TextRenderComp::Render()
{
	for (std::pair<Component*, std::string> pair : m_CompsToRender)
	{
		//check if the texture is something
		if (!pair.second.empty())
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

std::string TextRenderComp::MakeTextureFromText(const glm::vec3& color, const std::string& fontName, const std::string& text)
{
	const SDL_Color sdlColor = { Uint8(color.r * 255),Uint8(color.g * 255),Uint8(color.b * 255) };
	const auto surf = TTF_RenderText_Blended(
		ResourceManager::GetInstance().GetResource<Font>(fontName)->GetFont(),
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

	return ResourceManager::GetInstance().LoadTexture("FontTexture_" + m_pGameObj->GetScene()->GetName() + "_" + m_pGameObj->GetName(), texture);
}

void TextRenderComp::AddTextureToRender(Component* pComp, const std::string& name)
{
	//first we do a check if its already in the vector 
	auto it = std::find_if(m_CompsToRender.begin(), m_CompsToRender.end(), [pComp](const std::pair<Component*, std::string>& pair)
		{
			if (pair.first == pComp)
				return true;
			return false;
		});

	std::string newTextureName{ name };

	//if its already in there do not add the component again, just change the texture
	if (it != m_CompsToRender.end())
	{
		newTextureName = ResourceManager::GetInstance().ReplaceResource(it->second, name);
		(*it).second = newTextureName;
		return;
	}

	//else add it to the vector
	m_CompsToRender.push_back({ pComp,newTextureName });
}

void TextRenderComp::Notify(Component* pComp, Event event)
{
	if (event == Event::COMPONENT_TEXT_RENDER)
	{
		TextComp* pTextComp{ m_pGameObj->GetComponent<TextComp>(pComp->GetIdx()) };
		std::string textureName{ MakeTextureFromText(pTextComp->GetColor(), pTextComp->GetFontName(), pTextComp->GetText())};
		AddTextureToRender(pComp, textureName);
	}
}
