#pragma once
#include "Component.h"

class Font;

class TextComp final : public Component
{
public:
	explicit TextComp(const std::string& text, const std::string& fontFilePath, int fontSize);
	~TextComp();
	TextComp(const TextComp& other) = delete;
	TextComp(TextComp&& other) = delete;
	TextComp& operator=(const TextComp& other) = delete;
	TextComp& operator=(TextComp&& other) = delete;

	void Initialize() override;

	void SetText(const std::string& text);
	std::string GetText() const { return m_Text; };
	void SetFont(const std::string& fontFilePath);
	Font* GetFont() { return m_pFont; };
	void SetColor(const glm::vec3& color) { m_Color = color; };
	glm::vec3 GetColor() const { return m_Color; };
	void SetFontSize(int fontSize);
	int GetFontSize() const { return m_FontSize; };

private:
	std::string m_Text;
	Font* m_pFont;
	std::string m_FontFilePath;
	glm::vec3 m_Color;
	int m_FontSize;
};

