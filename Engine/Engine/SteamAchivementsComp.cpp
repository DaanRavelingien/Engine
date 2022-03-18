#include "EnginePCH.h"
#include "SteamAchivementsComp.h"
#include "Scene.h"
#include "GameObject.h"
#pragma warning(push)
#pragma warning(disable : 4996)
#include <steam_api.h>
#pragma warning(pop)

SteamAchivementsComp::SteamAchivementsComp(Scene* pScene)
	:Component(typeid(this).name())
	,m_pScene{pScene}
{
}

void SteamAchivementsComp::Initialize()
{
	//set this component to observe all components in the scene to check for any achievements in there
	for (GameObject* pGameObj : m_pScene->GetGameObjects())
	{
		pGameObj->AddObserver(this);
	}
}

void SteamAchivementsComp::Notify(Component*, Event event)
{
	if (event == Event::GAME_WON)
		SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
}
