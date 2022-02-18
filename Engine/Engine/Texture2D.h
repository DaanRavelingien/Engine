#pragma once
#include "Resource.h"

struct SDL_Texture;

/**
 * Simple RAII wrapper for an SDL_Texture
 */
class Texture2D final : public Resource
{
public:
	SDL_Texture* GetSDLTexture() const;
	explicit Texture2D(const std::string& name, const std::string& filePath);
	explicit Texture2D(const std::string& filePath);
	explicit Texture2D(SDL_Texture* texture);
	~Texture2D();

	Texture2D(const Texture2D &) = delete;
	Texture2D(Texture2D &&) = delete;
	Texture2D & operator= (const Texture2D &) = delete;
	Texture2D & operator= (const Texture2D &&) = delete;
private:
	void MakeTexture(const std::string& filePath);

	SDL_Texture* m_Texture;
};

