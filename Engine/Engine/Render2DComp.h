#pragma once
#include "Component.h"

class Font;
class Texture2D;

class Render2DComp final : public Component
{
public:
	explicit Render2DComp();
	~Render2DComp() = default;
	Render2DComp(const Render2DComp& other) = delete;
	Render2DComp(Render2DComp&& other) = delete;
	Render2DComp& operator=(const Render2DComp& other) = delete;
	Render2DComp& operator=(Render2DComp&& other) = delete;

	void Render();

	//static function to create comp from arguments
	static Component* CreateComp(const rapidjson::Value& args);
private:
	int MakeTextureFromText(const glm::vec3& color, int fontIdx, const std::string& text);
	void AddTextureToRender(Component* pComp, int textureIdx);

	void Notify(Component* pComp, Event event) override;

	std::vector<std::pair<Component*, int>> m_CompsToRender{};
};

