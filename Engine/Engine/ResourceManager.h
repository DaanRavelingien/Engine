#pragma once
#include "Singleton.h"
#include "Resource.h"

class Texture2D;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager();
	void Init(const std::string& data);
	Texture2D* LoadTexture(const std::string& file);
	Font* LoadFont(const std::string& file, unsigned int size);

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
	template<typename T>
	T* GetResource(const std::string& name) const
	{
		auto it = std::find_if(m_Resources.begin(), m_Resources.end(), [name](Resource* pResource)
			{
				if (dynamic_cast<T*>(pResource) && pResource->GetName() == name)
					return true;
				return false;
			});

		if (it == m_Resources.end())
		{
			LOGWARNING("No resource found of given type with given name");
			return nullptr;
		}

		return dynamic_cast<T*>(*it);
	}
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
	template<typename T>
	void RemoveResource(const std::string& name)
	{
		auto it = std::remove_if(m_Resources.begin(), m_Resources.end(), [name](Resource* pResource)
			{
				if (dynamic_cast<T*>(pResource) && pResource->GetName() == name)
					return true;
				return false;
			});

		if (it == m_Resources.end())
		{
			LOGWARNING("No resource found of given type with given name");
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
