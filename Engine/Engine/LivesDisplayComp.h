#pragma once
#include "Component.h"
#include "Observer.h"

class TextureComp;

class LivesDisplayComp : public Component, public Observer<Component>
{
public:
	LivesDisplayComp(GameObject* pObj, const std::string& liveTexturePath);
	LivesDisplayComp(GameObject* pObj, int livesTextureIdx);
	~LivesDisplayComp() = default;
	LivesDisplayComp(const LivesDisplayComp& other) = delete;
	LivesDisplayComp(LivesDisplayComp&& other) = delete;
	LivesDisplayComp& operator=(const LivesDisplayComp& other) = delete;
	LivesDisplayComp& operator=(LivesDisplayComp&& other) = delete;

	void Initialize() override;
private:
	GameObject* m_pObj{ nullptr };
	int m_LivesTextureIdx{};

	void Notify(Component* pComp, Event event) override;
};

