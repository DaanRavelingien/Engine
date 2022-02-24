#pragma once
#include "Component.h"

class Texture2D;

class TextureComp final : public Component
{
public:
	explicit TextureComp(const std::string& file);
	~TextureComp() = default;
	TextureComp(const TextureComp& other) = delete;
	TextureComp(TextureComp&& other) = delete;
	TextureComp& operator=(const TextureComp& other) = delete;
	TextureComp& operator=(TextureComp&& other) = delete;

	void Initialize() override;

	void ChangeTexture(const std::string& file);
	int GetTextureIdx() const { return m_TextureIdx; };

private:
	std::string m_FilePath{};
	int m_TextureIdx{};
};

