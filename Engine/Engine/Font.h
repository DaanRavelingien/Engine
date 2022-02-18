#pragma once
#include "Resource.h"

struct _TTF_Font;

/**
 * Simple RAII wrapper for an _TTF_Font
 */
class Font final : public Resource
{
public:
	_TTF_Font* GetFont() const;
	explicit Font(const std::string& name, const std::string& fullPath, unsigned int size);
	explicit Font(const std::string& fullPath, unsigned int size);
	~Font();

	Font(const Font &) = delete;
	Font(Font &&) = delete;
	Font & operator= (const Font &) = delete;
	Font & operator= (const Font &&) = delete;
private:
	void MakeFont(const std::string& filePath, unsigned int size);

	_TTF_Font* m_Font;
	unsigned int m_Size;
};

