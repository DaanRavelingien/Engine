#include "EnginePCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

ResourceManager::~ResourceManager()
{
	for (Resource* resource : m_Resources)
	{
		delete resource;
		resource = nullptr;
	}
}

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		LOGERROR("Failed to load support for png's: " + std::string{ SDL_GetError() });
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		LOGERROR("Failed to load support for jpg's: " + std::string{ SDL_GetError() });
	}

	if (TTF_Init() != 0) 
	{
		LOGERROR("Failed to load support for fonts: " + std::string{ SDL_GetError() });
	}
}

Texture2D* ResourceManager::LoadTexture(const std::string& file)
{
	Texture2D* pTexture{ new Texture2D{m_DataPath + file}};

	m_Resources.push_back(pTexture);

	return pTexture;
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	Font* pFont{ new Font{ m_DataPath + file, size } };
	
	m_Resources.push_back(pFont);

	return pFont;
}
