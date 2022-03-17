#pragma once
#include "Component.h"
#include "Observer.h"

class TextRenderComp : public Component, public Observer<Component>
{
public:
	explicit TextRenderComp();
	~TextRenderComp() = default;
	TextRenderComp(const TextRenderComp& other) = delete;
	TextRenderComp(TextRenderComp&& other) = delete;
	TextRenderComp& operator=(const TextRenderComp& other) = delete;
	TextRenderComp& operator=(TextRenderComp&& other) = delete;

	void Initialize() override;
	void Render();

private:
	int MakeTextureFromText(const glm::vec3& color, int fontIdx, const std::string& text);
	void AddTextureToRender(Component* pComp, int textureIdx);

	void Notify(Component* pComp, Event event) override;

	std::vector<std::pair<Component*, int>> m_CompsToRender{};
};

