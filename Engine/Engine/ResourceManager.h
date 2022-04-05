#pragma once
#include "Singleton.h"
#include <map>

class Resource;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager();
	void Init(const std::string& data);
	//creating resources
	std::string LoadTexture(const std::string& textureName, const std::string& file);
	std::string LoadTexture(const std::string& textureName, SDL_Texture* pTexture);
	std::string LoadFont(const std::string& fontName, const std::string& file, unsigned int size);
	
	//this function replaces the old resource with the new one given and then removes the new one from the list
	std::string ReplaceResource(const std::string& name, const std::string& otherName);

	std::string ReplaceTexture(const std::string& name, const std::string& newTextureFile);
	std::string ReplaceFont(const std::string& name, const std::string& newFontfile, unsigned int newFontSize);

	template<typename T>
	T* GetResource(const std::string& name) const
	{
		return dynamic_cast<T*>(m_Resources.at(name));
	}
	void RemoveResource(const std::string& name);

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;
	
	std::string m_DataPath;
	std::map<std::string, Resource*> m_Resources{};
};
