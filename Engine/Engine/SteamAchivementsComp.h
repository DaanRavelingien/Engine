#pragma once
#include "Component.h"
#include "Observer.h"

class Scene;

class SteamAchivementsComp : public Component, public Observer<Component>
{
public:
	SteamAchivementsComp(Scene* pScene);
	~SteamAchivementsComp() = default;
	SteamAchivementsComp(const SteamAchivementsComp& other) = delete;
	SteamAchivementsComp(SteamAchivementsComp&& other) = delete;
	SteamAchivementsComp& operator=(const SteamAchivementsComp& other) = delete;
	SteamAchivementsComp& operator=(SteamAchivementsComp&& other) = delete;

	void Initialize() override;
private:
	//the scene to monitor for achievements
	Scene* m_pScene{nullptr};

	int m_GamesWon{0};

	void Notify(Component* pComp, Event event) override;
};

