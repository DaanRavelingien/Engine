#pragma once
#include "Resource.h"

class ResourceManager;
struct _TTF_Font;

/**
 * Simple RAII wrapper for an _TTF_Font
 */
class Font final : public Resource
{
public:
	_TTF_Font* GetFont() const;

	Font(const Font &) = delete;
	Font(Font &&) = delete;
	Font & operator= (const Font &) = delete;
	Font & operator= (const Font &&) = delete;

	unsigned int GetFontSize() { return m_Size; };

private:
	friend class ResourceManager;
	//should only be created through the resource manager
	explicit Font(const std::string& fullPath, unsigned int size);
	~Font();

	void MakeFont(const std::string& filePath, unsigned int size);

	_TTF_Font* m_Font;
	unsigned int m_Size;
};

