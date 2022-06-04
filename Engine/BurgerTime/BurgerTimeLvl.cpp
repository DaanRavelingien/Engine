#include "BurgerTimeLvl.h"
#include <GameObject.h>
#include "glm\detail\type_vec4.hpp"
#include <ResourceManager.h>
#include <InputManager.h>

//component includes
#include <TextureComp.h>
#include <TransformComp.h>
#include "LivesDisplayComp.h"
#include "HealthComp.h"
#include "TextComp.h"
#include "ScoreCounterComp.h"
#include <TextRenderComp.h>
#include <TextureRenderComp.h>
#include "HitboxManagerComp.h"
#include "HitboxComp.h"
#include "EntityMoveComp.h"
#include "PlayerInputComp.h"
#include "LevelManagerComp.h"

void BurgerTimeLvl::Initialize()
{
	//setting the input controller amount to 1
	GetInputManager()->SetControllerAmount(1);

	//observing our own scene for events
	this->AddObserver(this);

	//creating a hitbox manager object
	//================================
	GameObject* pHitboxManager{ new GameObject{ "HitboxManager" } };
	HitboxManagerComp* pHitboxManagerComp{ new HitboxManagerComp{} };
	pHitboxManager->AddComponent(pHitboxManagerComp);
	AddGameObj(pHitboxManager);

	//creating peterPepper
	//====================
	m_pPeterPepper = new GameObject{ "PeterPepper" };
	m_pPeterPepper->AddComponent(new TextureRenderComp{});

	TextureComp* pPeterPepperTextureComp{ new TextureComp{"BurgerTimeTexture"} };
	pPeterPepperTextureComp->SetSourceRect({ 16,0,16,16 });
	pPeterPepperTextureComp->SetDestRect({ 0,0,16,16 });
	m_pPeterPepper->AddComponent(pPeterPepperTextureComp);
	m_pPeterPepper->AddComponent(new HealthComp{ 3 });
	m_pPeterPepper->AddComponent(new HitboxComp{ HitboxTag::Player, 16,16,
		HitboxManagerComp::CollisionGroup((int)HitboxManagerComp::CollisionGroup::CollisionGroup1 
			| (int)HitboxManagerComp::CollisionGroup::CollisionGroup2) });
	m_pPeterPepper->AddComponent(new EntityMoveComp{ glm::vec2{336,99} });
	m_pPeterPepper->AddComponent(new PlayerInputComp{});

	m_pPeterPepper->GetTransform()->SetScale({ 3,3,3 });
	AddGameObj(m_pPeterPepper);

	//creating hud
	//============
	GameObject* pHud{ new GameObject{ "Hud" } };
	//creating the display for the lives and score of player 1
	GameObject* pLivesDisplay{ new GameObject{"LivesDisplay"} };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pPeterPepper, "BurgerTimeTexture"));

	pLivesDisplay->GetTransform()->SetScale({ 3,3,3 });
	pLivesDisplay->GetTransform()->SetPos({ 10,700,0 });
	pHud->AddChild(pLivesDisplay);

	GameObject* pScoreDisplay{ new GameObject{ "ScoreDisplay" } };

	GameObject* pScoreLabel{ new GameObject{ "ScoreLabel" } };
	pScoreLabel->AddComponent(new TextRenderComp{});
	pScoreLabel->AddComponent(new TextComp{ "SCORE P1", "ArcadeClassic_Size50",{1,0,0} });
	pScoreLabel->GetTransform()->SetPos({ 0,0,0 });
	pScoreDisplay->AddChild(pScoreLabel);

	m_pScoreCounter = new GameObject{ "ScoreCount" };
	m_pScoreCounter->AddComponent(new TextRenderComp);
	m_pScoreCounter->AddComponent(new TextComp{ "0", "ArcadeClassic_Size50", {1,1,1} });
	m_pScoreCounter->AddComponent(new ScoreCounterComp{});
	m_pScoreCounter->GetTransform()->SetPos({ 0,40,0 });
	pScoreDisplay->AddChild(m_pScoreCounter);

	pScoreDisplay->GetTransform()->SetPos({ 20,10,0 });
	pHud->AddChild(pScoreDisplay);

	AddGameObj(pHud);

	//creating GameOver hud
	//=====================
	m_pGameOverHud = new GameObject{ "GameOverHud" };
	m_pGameOverHud->GetTransform()->SetPos({ 230,200,0 });

	GameObject* pGameOverLable{ new GameObject{ "GameOverLable" } };
	pGameOverLable->AddComponent(new TextRenderComp{});
	pGameOverLable->AddComponent(new TextComp{ "GAME OVER", "ArcadeClassic_Size100",{1,0,0} });
	pGameOverLable->GetTransform()->SetScale({ 0.5f,0.5f,0.5f });
	m_pGameOverHud->AddChild(pGameOverLable);

	GameObject* pHightScoreLable{ new GameObject{ "HightScoreLable" } };
	pHightScoreLable->AddComponent(new TextRenderComp{});
	pHightScoreLable->AddComponent(new TextComp{ "HIGH SCORE:", "ArcadeClassic_Size50",{1,0,0} });
	pHightScoreLable->GetTransform()->SetPos({ 0,40,0 });
	m_pGameOverHud->AddChild(pGameOverLable);

	GameObject* pScoreLable{ new GameObject{ "ScoreLable" } };
	pScoreLable->AddComponent(new TextRenderComp{});
	pScoreLable->AddComponent(new TextComp{ "YOUR SCORE:", "ArcadeClassic_Size50",{1,0,0} });
	pScoreLable->GetTransform()->SetPos({ 0,80,0 });
	m_pGameOverHud->AddChild(pScoreLable);

	m_pGameOverHud->Disable();
	AddGameObj(m_pGameOverHud);

	//creating the level from a json
	//==============================
	m_pLevel = new GameObject{"Level"};
	LevelManagerComp* pLevelManagerComp{ new LevelManagerComp{"BurgerTimeTexture"} };
	pLevelManagerComp->AddLevelFile("../Data/Levels/Level1.json");
	pLevelManagerComp->AddLevelFile("../Data/Levels/Level2.json");
	pLevelManagerComp->AddLevelFile("../Data/Levels/Level3.json");
	m_pLevel->AddComponent(pLevelManagerComp);
	m_pLevel->GetTransform()->SetScale({ 3,3,3 });
	m_pLevel->GetTransform()->SetPos({ 48,60,-1 });
	AddGameObj(m_pLevel);
}

void BurgerTimeLvl::OnSceneActivated()
{
	//setting up the correct input
	GetInputManager()->SetCommand(KeyboardButton::ESC, ButtonState::Up, new PauseCmd{ nullptr });
	GetInputManager()->SetCommand(ControllerButton::StartButton, ButtonState::Up, new PauseCmd{ nullptr }, Controller::Controller_1);
	GetInputManager()->SetCommand(ControllerButton::BackButton, ButtonState::Up, new PauseCmd{ nullptr }, Controller::Controller_1);

	//resetting the score
	m_pScoreCounter->GetComponent<ScoreCounterComp>()->Reset();

	//hiding the game over Display
	m_pGameOverHud->Disable();

	//respawning the player characters
	m_pPeterPepper->Enable();
	m_pPeterPepper->GetComponent<EntityMoveComp>()->Respawn();
}

void BurgerTimeLvl::OnSceneDeactivated()
{
	//resetting the level after leaving the scene so we dont see any flickering
	m_pLevel->GetComponent<LevelManagerComp>()->ResetLvl();

	//removing the game over input
	GetInputManager()->RemoveCommands(KeyboardButton::ESC, ButtonState::Up);
	GetInputManager()->RemoveCommands(KeyboardButton::ENTER, ButtonState::Up);
	GetInputManager()->RemoveCommands(ControllerButton::ButtonA, ButtonState::Up, Controller::Controller_1);
}

void BurgerTimeLvl::PauseCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimePauseMenu");
}

void BurgerTimeLvl::GameOverCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimeMainMenu");
}

void BurgerTimeLvl::Notify(Component*, Event event)
{
	if (event == Event::PLAYER_DIED)
	{
		//remove the pause commands
		GetInputManager()->RemoveCommands(KeyboardButton::ESC, ButtonState::Up);
		GetInputManager()->RemoveCommands(ControllerButton::StartButton, ButtonState::Up, Controller::Controller_1);
		GetInputManager()->RemoveCommands(ControllerButton::BackButton, ButtonState::Up, Controller::Controller_1);

		//setting up the game over commands
		GetInputManager()->SetCommand(KeyboardButton::ESC, ButtonState::Up, new GameOverCmd{ nullptr });
		GetInputManager()->SetCommand(KeyboardButton::ENTER, ButtonState::Up, new GameOverCmd{ nullptr });
		GetInputManager()->SetCommand(ControllerButton::ButtonA, ButtonState::Up, new GameOverCmd{ nullptr }, Controller::Controller_1);

		//enabeling the game over hud
		m_pGameOverHud->Enable();

		//disabeling the player character so no more input can be given
		m_pPeterPepper->Disable();
	}
}