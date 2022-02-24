#include "EnginePCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Resource.h"
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

int ResourceManager::LoadTexture(const std::string& file)
{
	Texture2D* pTexture{ new Texture2D{m_DataPath + file}};

	m_Resources.push_back(pTexture);

	return pTexture->GetIdx();
}

int ResourceManager::LoadTexture(SDL_Texture* pTexture)
{
	Texture2D* pNewTexture{ new Texture2D{pTexture} };

	m_Resources.push_back(pNewTexture);

	return pNewTexture->GetIdx();
}

int ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	Font* pFont{ new Font{ m_DataPath + file, size } };
	
	m_Resources.push_back(pFont);

	return pFont->GetIdx();
}

int ResourceManager::ReplaceResource(int oldResource, int newResource)
{
	//finding the texture to replace
	auto itOld = std::find_if(m_Resources.begin(), m_Resources.end(), [oldResource](Resource* pResource)
		{
			if (pResource->GetIdx() == oldResource)
				return true;
			return false;
		});

	//finding the texture to replace it with and placing that one at the back
	auto itNew = std::remove_if(m_Resources.begin(), m_Resources.end(), [newResource](Resource* pResource)
		{
			if (pResource->GetIdx() == newResource)
				return true;
			return false;
		});

	if (itOld == m_Resources.end())
	{
		LOGWARNING("No resources found with given idx to replace");
		return -1;
	}
	if (itNew == m_Resources.end())
	{
		LOGWARNING("No resources found with given idx to replace the other texture with");
		return -1;
	}

	//we will keep the same idx
	int idx{ (*itOld)->GetIdx() };

	//deleting the old texture
	delete* itOld;
	*itOld = nullptr;

	//making the new texture and placing it in the old textures place
	*itOld = *itNew;
	(*itOld)->m_Idx = idx;

	//removing the other resource from our vector
	m_Resources.erase(itNew, m_Resources.end());

	return (*itOld)->GetIdx();
}

int ResourceManager::ReplaceTexture(int idxOldTexture, const std::string& newTextureFile)
{
	//finding the texture to replace
	auto it = std::find_if(m_Resources.begin(), m_Resources.end(), [idxOldTexture](Resource* pResource) 
		{
			if (pResource->GetIdx() == idxOldTexture)
				return true;
			return false;
		});

	if (it == m_Resources.end())
	{
		LOGWARNING("No texture found with given idx to replace");
		return -1;
	}

	//we will keep the same idx
	int idx{ (*it)->GetIdx() };

	//deleting the old texture
	delete* it;
	*it = nullptr;

	//making the new texture and placing it in the old textures place
	*it = new Texture2D{ idx, m_DataPath + newTextureFile };

	return (*it)->GetIdx();
}

int ResourceManager::ReplaceFont(int idxOldFont, const std::string& newFontfile, unsigned int newFontSize)
{
	//finding the font we want to replace
	auto it = std::find_if(m_Resources.begin(), m_Resources.end(), [idxOldFont](Resource* pResource)
		{
			if (pResource->GetIdx() == idxOldFont)
				return true;
			return false;
		});

	if (it == m_Resources.end())
	{
		LOGWARNING("No Font found with given idx to replace");
		return -1;
	}

	//we will keep the same idx
	int idx{ (*it)->GetIdx() };

	//deleting the old font
	delete* it;
	*it = nullptr;

	//creating the new font and placing it in the place of the old one
	*it = new Font{ idx,m_DataPath + newFontfile, newFontSize };

	return (*it)->GetIdx();
}

void ResourceManager::RemoveResource(int idx)
{
	auto it = std::remove_if(m_Resources.begin(), m_Resources.end(), [idx](Resource* pResource)
		{
			if (pResource->GetIdx() == idx)
				return true;
			return false;
		});

	if (it == m_Resources.end())
	{
		LOGWARNING("No resource found with given idx");
		return;
	}

	delete* it;
	*it = nullptr;

	m_Resources.erase(it, m_Resources.end());
}
