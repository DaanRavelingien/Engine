#pragma once
#include "Component.h"
#include "Observer.h"

class Font;
class Texture2D;

class Render2DComp final : public Component, public Observer<Component>
{
public:
	explicit Render2DComp();
	~Render2DComp() = default;
	Render2DComp(const Render2DComp& other) = delete;
	Render2DComp(Render2DComp&& other) = delete;
	Render2DComp& operator=(const Render2DComp& other) = delete;
	Render2DComp& operator=(Render2DComp&& other) = delete;

	void Initialize() override;
	void Render();

private:
	int MakeTextureFromText(const glm::vec3& color, int fontIdx, const std::string& text);
	void AddTextureToRender(Component* pComp, int textureIdx);

	void Notify(Component* pComp, Event event) override;

	std::vector<std::pair<Component*, int>> m_CompsToRender{};
};

