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

protected:
	friend class ResourceManager;

	Resource() = default;
	virtual ~Resource() = default;
};

