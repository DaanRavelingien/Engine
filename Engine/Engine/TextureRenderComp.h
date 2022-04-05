#pragma once
#include "Component.h"
#include "Observer.h"

class TextureRenderComp : public Component, public Observer<Component>
{
public:
	explicit TextureRenderComp();
	~TextureRenderComp() = default;
	TextureRenderComp(const TextureRenderComp& other) = delete;
	TextureRenderComp(TextureRenderComp&& other) = delete;
	TextureRenderComp& operator=(const TextureRenderComp& other) = delete;
	TextureRenderComp& operator=(TextureRenderComp&& other) = delete;

	void Initialize() override;
	void Render();

private:
	void AddTextureToRender(Component * pComp, const std::string& name);

	void Notify(Component * pComp, Event event) override;

	std::vector<std::pair<Component*, std::string>> m_CompsToRender{};
};

