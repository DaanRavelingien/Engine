#pragma once
#include "Component.h"

class Font;
class Texture2D;

class Render2DComp final : public Component
{
public:
	explicit Render2DComp() = default;
	~Render2DComp();
	Render2DComp(const Render2DComp& other) = delete;
	Render2DComp(Render2DComp&& other) = delete;
	Render2DComp& operator=(const Render2DComp& other) = delete;
	Render2DComp& operator=(Render2DComp&& other) = delete;

	void Render();

private:
	Texture2D* MakeTextureFromText(const glm::vec3& color, Font* pFont, const std::string& text);
	void AddCompToRender(Component* pComp, Texture2D* pTexture);

	void Notify(Component* pComp, Event event) override;

	std::vector<std::pair<Component*, Texture2D*>> m_CompsToRender{};
};

