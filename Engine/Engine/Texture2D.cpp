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

glm::vec2 Texture2D::GetTextureSize() const
{
	int textureWidth{};
	int textureHeight{};

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &textureWidth, &textureHeight);
	
	return glm::vec2{ textureWidth,textureHeight };
}

Texture2D::Texture2D(int idx, const std::string& filePath)
	:Resource(idx)
	,m_Texture{nullptr}
{
	MakeTexture(filePath);
}

Texture2D::Texture2D(const std::string& filePath)
	:Resource()
	, m_Texture{nullptr}
{
	MakeTexture(filePath);
}

Texture2D::Texture2D(int idx, SDL_Texture* pTexture)
	:Resource(idx)
	,m_Texture{pTexture}
{
}

Texture2D::Texture2D(SDL_Texture* pTexture)
	:Resource()
	, m_Texture{pTexture}
{
}
