#pragma once
#include "Component.h"

class TransformComp;
class Texture2D;

class TextureComp final : public Component
{
public:
	explicit TextureComp(const std::string& textureName);
	~TextureComp() = default;
	TextureComp(const TextureComp& other) = delete;
	TextureComp(TextureComp&& other) = delete;
	TextureComp& operator=(const TextureComp& other) = delete;
	TextureComp& operator=(TextureComp&& other) = delete;

	void Initialize() override;

	void ChangeTexture(const std::string& newTextureName);
	std::string GetTextureName() const { return m_TextureName; };

	void SetSourceRect(const glm::vec4& rect) { m_SourceRect = rect; };
	glm::vec4 GetSourceRect() const { return m_SourceRect; };
	void SetDestRect(const glm::vec4& rect) { m_DestRect = rect; };
	glm::vec4 GetDestRect() const;

private:
	std::string m_TextureName{};
	glm::vec4 m_SourceRect{};
	glm::vec4 m_DestRect{};
};

