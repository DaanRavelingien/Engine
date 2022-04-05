#include "EnginePCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Resource.h"
#include "Texture2D.h"
#include "Font.h"

ResourceManager::~ResourceManager()
{
	for (std::pair<std::string, Resource*> resource : m_Resources)
	{
		delete resource.second;
		resource.second = nullptr;
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

std::string ResourceManager::LoadTexture(const std::string& textureName, const std::string& file)
{
	Texture2D* pTexture{ new Texture2D{m_DataPath + file}};

	//checking if we are not overriding already existing textures
	if (m_Resources.find(textureName) != m_Resources.end())
		LOGWARNING("replacing a resource that already exists");

	m_Resources.emplace(std::pair<std::string, Resource*>{textureName, pTexture});

	return textureName;
}

std::string ResourceManager::LoadTexture(const std::string& textureName, SDL_Texture* pTexture)
{
	Texture2D* pNewTexture{ new Texture2D{pTexture} };

	//checking if we are not overriding already existing textures
	if (m_Resources.find(textureName) != m_Resources.end())
		LOGWARNING("replacing a resource that already exists");

	m_Resources.emplace(std::pair<std::string, Resource*>{textureName, pNewTexture});

	return textureName;
}

std::string ResourceManager::LoadFont(const std::string& fontName ,const std::string& file, unsigned int size)
{
	Font* pFont{ new Font{ m_DataPath + file, size } };
	
	m_Resources.emplace(std::pair<std::string, Resource*>{fontName, pFont});

	return fontName;
}

std::string ResourceManager::ReplaceResource(const std::string& name, const std::string& otherName)
{
	Resource* pOldResource{ m_Resources.at(name) };
	Resource* pNewResource{ m_Resources.at(otherName) };

	//replacing the old resource 
	delete pOldResource;
	pOldResource = pNewResource;

	//removing the new resource
	m_Resources.erase(otherName);

	return name;
}

std::string ResourceManager::ReplaceTexture(const std::string& name, const std::string& newTextureFile)
{
	Resource* pOldResource{ m_Resources.at(name) };

	//replacing the resource with the new one
	delete pOldResource;
	pOldResource = new Texture2D{ newTextureFile };

	return name;
}

std::string ResourceManager::ReplaceFont(const std::string& name, const std::string& newFontfile, unsigned int newFontSize)
{
	Resource* pOldResource{ m_Resources.at(name) };

	//replacing the old font
	delete pOldResource;
	pOldResource = new Font{ m_DataPath + newFontfile, newFontSize };

	return name;
}

void ResourceManager::RemoveResource(const std::string& name)
{
	m_Resources.erase(name);
}
