#pragma once
#include "Component.h"

class TextureComp;

class SpriteComp final : public Component
{
public:
	//the sprite component is assuming that the frames are placed horizontally after each other in one line
	explicit SpriteComp(int frames,const glm::vec2& framePxlSize, const glm::vec2& startFramePos, float frameTime);
	~SpriteComp() = default;
	SpriteComp(const SpriteComp& other) = delete;
	SpriteComp(SpriteComp&& other) = delete;
	SpriteComp& operator=(const SpriteComp& other) = delete;
	SpriteComp& operator=(SpriteComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	//static function to create comp from arguments
	static Component* CreateComp(const rapidjson::Value& args);
private:
	int m_FrameCount{};
	glm::vec2 m_FramePxlSize{};
	glm::vec2 m_StartFramePos{};
	float m_FrameTime{};
	int m_CurrentFrame{};
	float m_ElapsedFrameTime{};

	TextureComp* m_pTextureComp{ nullptr };
};

