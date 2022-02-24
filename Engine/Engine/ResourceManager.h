#pragma once
#include "Singleton.h"

class Resource;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager();
	void Init(const std::string& data);
	//creating resources
	int LoadTexture(const std::string& file);
	int LoadTexture(SDL_Texture* pTexture);
	int LoadFont(const std::string& file, unsigned int size);
	
	//this function replaces the old resource with the new one given and then removes the new one from the list
	int ReplaceResource(int oldResource, int newResource);

	int ReplaceTexture(int idxOldTexture, const std::string& newTextureFile);
	int ReplaceFont(int idxOldFont, const std::string& newFontfile, unsigned int newFontSize);

	template<typename T>
	T* GetResource(int idx) const
	{
		auto it = std::find_if(m_Resources.begin(), m_Resources.end(), [idx](Resource* pResource)
			{
				if (dynamic_cast<T*>(pResource) && pResource->GetIdx() == idx)
					return true;
				return false;
			});

		if (it == m_Resources.end())
		{
			LOGWARNING("No resource found of given type with given id");
			return nullptr;
		}

		return dynamic_cast<T*>(*it);
	}
	void RemoveResource(int idx);
	template<typename T>
	void RemoveResource(int idx)
	{
		auto it = std::remove_if(m_Resources.begin(), m_Resources.end(), [idx](Resource* pResource)
			{
				if (dynamic_cast<T*>(pResource) && pResource->GetIdx() == idx)
					return true;
				return false;
			});

		if (it == m_Resources.end())
		{
			LOGWARNING("No resource found of given type with given idx");
			return;
		}

		delete* it;
		*it = nullptr;

		m_Resources.erase(it, m_Resources.end());
	}

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;
	
	std::string m_DataPath;
	std::vector<Resource*> m_Resources{};
};
