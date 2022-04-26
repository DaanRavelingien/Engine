#include "EnginePCH.h"
#include "ScoreCounterComp.h"
#include "GameObject.h"
#include "TextComp.h"
#include "Scene.h"

ScoreCounterComp::ScoreCounterComp()
	:Component{ typeid(this).name() }
{
}

void ScoreCounterComp::Initialize()
{
	//adding this component as an observer to the scene
	m_pGameObj->GetScene()->AddObserver(this);
}

void ScoreCounterComp::Notify(Component*, Event event)
{
	if (event == Event::BURGER_DROPS)
	{
		m_Score += 50;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::HOTDOG_DIES)
	{
		m_Score += 100;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::PICLE_DIES)
	{
		m_Score += 200;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::EGG_DIES)
	{
		m_Score += 300;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::BURGER_DROPS_1_ENEMY)
	{
		m_Score += 500;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::BURGER_DROPS_2_ENEMYS)
	{
		m_Score += 1000;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::BURGER_DROPS_3_ENEMYS)
	{
		m_Score += 2000;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::BURGER_DROPS_4_ENEMYS)
	{
		m_Score += 4000;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::BURGER_DROPS_5_ENEMYS)
	{
		m_Score += 8000;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
	if (event == Event::BURGER_DROPS_6_ENEMYS)
	{
		m_Score += 16000;
		m_pGameObj->GetComponent<TextComp>()->SetText(std::to_string(m_Score));
	}
}
