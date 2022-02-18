#include "EnginePCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Font::GetFont() const {
	return m_Font;
}

Font::Font(const std::string& name, const std::string& fullPath, unsigned int size) 
	: Resource(name)
	, m_Font(nullptr)
	, m_Size(size)
{
	MakeFont(fullPath, size);
}

Font::Font(const std::string& fullPath, unsigned int size)
	:Resource("")
{
	//if not name was given just set the id as name
	std::string name{ "Font" + GetIdx() };
	Rename(name);

	MakeFont(fullPath, size);
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}

void Font::MakeFont(const std::string& filePath, unsigned int size)
{
	m_Font = TTF_OpenFont(filePath.c_str(), size);
	if (m_Font == nullptr)
		LOGERROR("Failed to load font: " + std::string{ SDL_GetError() });
}
