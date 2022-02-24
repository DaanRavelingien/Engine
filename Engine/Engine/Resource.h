#pragma once
#include "ResourceManager.h"

class ResourceManager;

class Resource
{
public:
	Resource(const Resource&) = delete;
	Resource(Resource&&) = delete;
	Resource& operator= (const Resource&) = delete;
	Resource& operator= (const Resource&&) = delete;

	int GetIdx() const { return m_Idx; };

protected:
	friend class ResourceManager;

	Resource();
	Resource(int idx);
	virtual ~Resource() = default;

private:
	int m_Idx;

	static int m_ResourceCounter;
};

