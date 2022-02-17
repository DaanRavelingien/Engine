#pragma once
#include "Component.h"

class Texture2D;

class TextureComp final : public Component
{
public:
	explicit TextureComp(const std::string& filePath);
	~TextureComp();
	TextureComp(const TextureComp& other) = delete;
	TextureComp(TextureComp&& other) = delete;
	TextureComp& operator=(const TextureComp& other) = delete;
	TextureComp& operator=(TextureComp&& other) = delete;

	void Initialize() override;

	void ChangeTexture(const std::string& filePath);
	Texture2D* GetTexture() const { return m_pTexture; };

private:
	std::string m_FilePath{};
	Texture2D* m_pTexture{};
};

