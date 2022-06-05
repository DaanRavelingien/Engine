#include "BurgerTimeGameOver.h"
#include <GameObject.h>
#include <InputManager.h>
#include "BurgerTimeData.h"
#include "SoundSystem.h"

//component includes
#include "TextRenderComp.h"
#include "TextComp.h"
#include <TransformComp.h>

void BurgerTimeGameOver::Initialize()
{
	//loading the sound for the level
	//===============================
	GetSoundSystem()->LoadSound("GameOver", "../Data/Sound/GameOverFx.wav");

	//setting the input controller amount to 2
	GetInputManager()->SetControllerAmount(1);

	//creating general input for the scene
	//====================================
	GetInputManager()->SetCommand(KeyboardButton::ESC, ButtonState::Up, new ContiniuCmd{ nullptr });
	GetInputManager()->SetCommand(KeyboardButton::ENTER, ButtonState::Up, new ContiniuCmd{ nullptr });
	GetInputManager()->SetCommand(ControllerButton::ButtonA, ButtonState::Up, new ContiniuCmd{ nullptr }, Controller::Controller_1);

	//creating GameOver hud
	//=====================
	GameObject* pGameOverDispl{ new GameObject{ "GameOverHud" } };
	pGameOverDispl->GetTransform()->SetPos({ 140,200,0 });

	GameObject* pGameOverLable{ new GameObject{ "GameOverLable" } };
	pGameOverLable->AddComponent(new TextRenderComp{});
	pGameOverLable->AddComponent(new TextComp{ "GAME OVER", "ArcadeClassic_Size100",{1,0,0} });
	pGameOverLable->GetTransform()->SetScale({ 0.5f,0.5f,0.5f });
	pGameOverDispl->AddChild(pGameOverLable);

	m_pHighScoreLable = new GameObject{ "HightScoreLable" };
	m_pHighScoreLable->AddComponent(new TextRenderComp{});
	m_pHighScoreLable->AddComponent(new TextComp{ "HIGH SCORE", "ArcadeClassic_Size50",{1,1,1} });
	m_pHighScoreLable->GetTransform()->SetPos({ 0,80,0 });
	pGameOverDispl->AddChild(m_pHighScoreLable);

	m_pScoreLable = new GameObject{ "ScoreLable" };
	m_pScoreLable->AddComponent(new TextRenderComp{});
	m_pScoreLable->AddComponent(new TextComp{ "YOUR SCORE", "ArcadeClassic_Size50",{1,1,1} });
	m_pScoreLable->GetTransform()->SetPos({ 0,120,0 });
	pGameOverDispl->AddChild(m_pScoreLable);

	AddGameObj(pGameOverDispl);
}

void BurgerTimeGameOver::OnSceneActivated()
{
	//getting the previous scene name
	std::string prevSceneName{ SceneManager::GetInstance().GetPrevActiveScene()->GetName() };
	BurgerTimeData::GameMode gameMode{};

	if (prevSceneName.compare("BurgerTimeLvl") == 0)
		gameMode = BurgerTimeData::GameMode::Single;
	if (prevSceneName.compare("BurgerTimeCoOpLvl") == 0)
		gameMode = BurgerTimeData::GameMode::CoOp;
	if (prevSceneName.compare("BurgerTimeVsLvl") == 0)
		gameMode = BurgerTimeData::GameMode::Vs;

	int highScore{ BurgerTimeData::GetInstance().GetHeighScore(gameMode) };
	int score{ BurgerTimeData::GetInstance().GetScore(gameMode) };

	m_pHighScoreLable->GetComponent<TextComp>()->SetText("HIGHSCORE    " + std::to_string(highScore));
	m_pScoreLable->GetComponent<TextComp>()->SetText("YOUR SCORE    " + std::to_string(score));

	//play sound
	GetSoundSystem()->ContiniuMusic();
	GetSoundSystem()->PlayASound("GameOver", (float)BurgerTimeData::GetInstance().GetGameVolume());
}

void BurgerTimeGameOver::OnSceneDeactivated()
{
	//stop sound
	GetSoundSystem()->PauseMusic();
}

void BurgerTimeGameOver::ContiniuCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimeMainMenu");
}
