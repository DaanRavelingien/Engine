#include "EnginePCH.h"
#include "ScoreCounterComp.h"
#include "GameObject.h"
#include "TextComp.h"

ScoreCounterComp::ScoreCounterComp()
	:Component{ typeid(this).name() }
{
}

void ScoreCounterComp::Initialize()
{
	//subscribing to get notified if enemies die
	//should probably be an enemy manager and burger manager or something
	m_pGameObj->AddObserver(this);
}

void ScoreCounterComp::Notify(Component*, Event event)
{
	if (event == Event::COMPONENT_BURGER_DROPS)
	{
		m_Score += 100;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::COMPONENT_ENEMY_DIES)
	{
		m_Score += 200;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
}
