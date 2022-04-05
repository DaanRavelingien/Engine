#pragma once
#include "Component.h"

class Font;

class TextComp final : public Component
{
public:
	explicit TextComp(const std::string& text, const std::string& fontName, const glm::vec3& color = glm::vec3{ 1,1,1 });
	~TextComp() = default;
	TextComp(const TextComp& other) = delete;
	TextComp(TextComp&& other) = delete;
	TextComp& operator=(const TextComp& other) = delete;
	TextComp& operator=(TextComp&& other) = delete;

	void Initialize() override;

	void SetText(const std::string& text);
	std::string GetText() const { return m_Text; };
	void SetFont(const std::string& file);
	std::string GetFontName() { return m_FontName; };
	void SetColor(const glm::vec3& color) { m_Color = color; };
	glm::vec3 GetColor() const { return m_Color; };
	void SetFontSize(unsigned int fontSize);
	unsigned int GetFontSize() const;

private:
	std::string m_Text;
	std::string m_FontName;
	glm::vec3 m_Color;
};

