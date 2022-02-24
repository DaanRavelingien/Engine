#pragma once
#include "Resource.h"

class ResourceManager;
struct SDL_Texture;

/**
 * Simple RAII wrapper for an SDL_Texture
 */
class Texture2D final : public Resource
{
public:
	SDL_Texture* GetSDLTexture() const;

	Texture2D(const Texture2D &) = delete;
	Texture2D(Texture2D &&) = delete;
	Texture2D & operator= (const Texture2D &) = delete;
	Texture2D & operator= (const Texture2D &&) = delete;
private:
	friend class ResourceManager;
	//should be created through the resource manager
	explicit Texture2D(int idx, const std::string& filePath);
	explicit Texture2D(const std::string& filePath);
	explicit Texture2D(int idx, SDL_Texture* pTexture);
	explicit Texture2D(SDL_Texture* pTexture);
	~Texture2D();

	void MakeTexture(const std::string& filePath);

	SDL_Texture* m_Texture;
};

