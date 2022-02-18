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

Render2DComp::~Render2DComp()
{
	for (std::pair<Component*, Texture2D*> pair : m_CompsToRender)
	{
		//deleting the textures the render comp created for our text
		if (dynamic_cast<TextComp*>(pair.first) != NULL)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

void Render2DComp::Render()
{
	for (std::pair<Component*, Texture2D*> pair : m_CompsToRender)
	{
		//check if the texture is something
		if (pair.second)
		{
			const auto& pos = m_pGameObj->GetTransform()->GetPos();
			Renderer::GetInstance().RenderTexture(*pair.second, pos.x, pos.y);
		}
		else
		{
			LOGWARNING("a texture was nullptr");
		}
	}
}

Texture2D* Render2DComp::MakeTextureFromText(const glm::vec3& color, Font* pFont, const std::string& text)
{
	const SDL_Color sdlColor = { Uint8(color.r * 255),Uint8(color.g * 255),Uint8(color.b * 255) };
	const auto surf = TTF_RenderText_Blended(pFont->GetFont(), text.c_str(), sdlColor);
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

	return new Texture2D{ texture };
}

void Render2DComp::AddCompToRender(Component* pComp, Texture2D* pTexture)
{
	//first we do a check if its already in the vector 
	auto it = std::find_if(m_CompsToRender.begin(), m_CompsToRender.end(), [pComp](const std::pair<Component*, Texture2D*>& pair)
		{
			if (pair.first == pComp)
				return true;
			return false;
		});

	//if its already in there do not add the component again, just change the texture
	if (it != m_CompsToRender.end())
	{
		//remove the old texture;
		delete it->second;
		it->second = nullptr;

		//add the new one
		it->second = pTexture;
		return;
	}

	//else add it to the vector
	m_CompsToRender.push_back({ pComp,pTexture });
}

void Render2DComp::Notify(Component* pComp, Event event)
{
	TextComp* pTextComp{nullptr};
	Texture2D* pTexture{ nullptr };
	TextureComp* pTextureComp{ nullptr };

	switch (event)
	{
	case Event::COMPONENT_TEXT_RENDER:
		pTextComp = m_pGameObj->GetComponent<TextComp>(pComp->GetIdx());
		pTexture = MakeTextureFromText(pTextComp->GetColor(), pTextComp->GetFont(), pTextComp->GetText());
		AddCompToRender(pComp, pTexture);
		break;

	case Event::COMPONENT_TEXTURE_RENDER:
		pTextureComp = m_pGameObj->GetComponent<TextureComp>(pComp->GetIdx());
		AddCompToRender(pComp, pTextureComp->GetTexture());
		break;

	default:
		break;
	}
}
