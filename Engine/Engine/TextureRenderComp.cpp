#include "EnginePCH.h"
#include "TextureRenderComp.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

//component includes
#include "TransformComp.h"
#include "TextureComp.h"

TextureRenderComp::TextureRenderComp()
	:Component{typeid(this).name()}
{
}

void TextureRenderComp::Initialize()
{
	m_pGameObj->AddObserver(this);
}

void TextureRenderComp::Render()
{
	for (std::pair<Component*, int> pair : m_CompsToRender)
	{
		//check if the texture is something
		if (pair.second >= 0)
		{
			TextureComp* pTextureComp{ dynamic_cast<TextureComp*>(pair.first) };

			Renderer::GetInstance().RenderTexture(
				*ResourceManager::GetInstance().GetResource<Texture2D>(pair.second),
				pTextureComp->GetDestRect(), pTextureComp->GetSourceRect());
		}
		else
		{
			LOGWARNING("the resource idx was invalid");
		}
	}
}

void TextureRenderComp::AddTextureToRender(Component* pComp, int textureIdx)
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
		(*it).second = newTextureIdx;
		return;
	}

	//else add it to the vector
	m_CompsToRender.push_back({ pComp,newTextureIdx });
}

void TextureRenderComp::Notify(Component* pComp, Event event)
{
	if (event == Event::COMPONENT_TEXTURE_RENDER)
	{
		TextureComp* pTextureComp{ m_pGameObj->GetComponent<TextureComp>(pComp->GetIdx()) };
		AddTextureToRender(pComp, pTextureComp->GetTextureIdx());
	}
}
