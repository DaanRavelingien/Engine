#include "EnginePCH.h"
#include "Texture2D.h"
#include <SDL_image.h>
#include "Renderer.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

void Texture2D::MakeTexture(const std::string& filePath)
{
	const auto fullPath = filePath;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		LOGERROR("Failed to load texture: " + std::string{ SDL_GetError() });
	}

	m_Texture = texture;
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Texture2D::Texture2D(const std::string& name, const std::string& filePath)
	:Resource(name)
	, m_Texture{nullptr}
{
	MakeTexture(filePath);
}

Texture2D::Texture2D(const std::string& filePath)
	:Resource("")
	, m_Texture{nullptr}
{
	//if not name was given just set the id as name
	std::string name{ "Texture2D" + GetIdx() };
	Rename(name);

	MakeTexture(filePath);
}

Texture2D::Texture2D(SDL_Texture* texture)
	:Resource("")
	, m_Texture{texture}
{
	//if not name was given just set the id as name
	std::string name{ "Texture2D" + GetIdx() };
	Rename(name);
}
