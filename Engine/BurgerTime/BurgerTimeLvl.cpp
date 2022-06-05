#include "BurgerTimeLvl.h"
#include <GameObject.h>
#include "glm\detail\type_vec4.hpp"
#include <ResourceManager.h>
#include <InputManager.h>
#include "BurgerTimeData.h"

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
#include "GravityComp.h"
#include "EnemyComp.h"
#include "EnemyManagerComp.h"

void BurgerTimeLvl::Initialize()
{
	//setting the input controller amount to 1
	GetInputManager()->SetControllerAmount(1);

	//setting up the correct input
	GetInputManager()->SetCommand(KeyboardButton::ESC, ButtonState::Up, new PauseCmd{ nullptr });
	GetInputManager()->SetCommand(ControllerButton::StartButton, ButtonState::Up, new PauseCmd{ nullptr }, Controller::Controller_1);
	GetInputManager()->SetCommand(ControllerButton::BackButton, ButtonState::Up, new PauseCmd{ nullptr }, Controller::Controller_1);

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

	//creating the enemy manager
	//==========================
	m_pEnemyManager = new GameObject{ "EnemyManager" };
	EnemyManagerComp* pEnemyManagerComp{ new EnemyManagerComp{6} };
	m_pEnemyManager->AddComponent(pEnemyManagerComp);
	pEnemyManagerComp->AddSpawnPoint(glm::vec3{ 48,99,0 });
	pEnemyManagerComp->AddSpawnPoint(glm::vec3{ 624,99,0 });
	pEnemyManagerComp->AddEnemyTarget(m_pPeterPepper);

	AddGameObj(m_pEnemyManager);

	//creating hud
	//============
	GameObject* pHud{ new GameObject{ "Hud" } };
	//creating the display for the lives and score of player 1
	GameObject* pLivesDisplay{ new GameObject{"LivesDisplay"} };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pPeterPepper, "BurgerTimeTexture"));

	pLivesDisplay->GetTransform()->SetScale({ 4,4,4 });
	pLivesDisplay->GetTransform()->SetPos({ 10,700,0 });
	pHud->AddChild(pLivesDisplay);

	GameObject* pScoreDisplay{ new GameObject{ "ScoreDisplay" } };

	GameObject* pScoreLabel{ new GameObject{ "ScoreLabel" } };
	pScoreLabel->AddComponent(new TextRenderComp{});
	pScoreLabel->AddComponent(new TextComp{ "SCORE", "ArcadeClassic_Size50",{1,0,0} });
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
	//respawning the player characters when we come to this scene
	m_pPeterPepper->GetComponent<EntityMoveComp>()->Respawn();

	m_pEnemyManager->GetComponent<EnemyManagerComp>()->ResetEnemies();
}

void BurgerTimeLvl::PauseCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimePauseMenu");
}

void BurgerTimeLvl::Notify(Component*, Event event)
{
	if (event == Event::PLAYER_DAMAGED)
	{
		//resetting the enemies
		m_pEnemyManager->GetComponent<EnemyManagerComp>()->ResetEnemies();
	}
	if (event == Event::PLAYER_DIED)
	{
		//updating the high score
		int HighScore{ BurgerTimeData::GetInstance().GetHeighScore(BurgerTimeData::GameMode::Single) };
		int currScore{ m_pScoreCounter->GetComponent<ScoreCounterComp>()->GetScore() };

		if (HighScore < currScore)
			BurgerTimeData::GetInstance().SetHeighScore(BurgerTimeData::GameMode::Single, currScore);
		BurgerTimeData::GetInstance().SetScore(BurgerTimeData::GameMode::Single, currScore);

		//resetting the scene
		ResetScene();

		//also setting the 1s level again
		m_pLevel->GetComponent<LevelManagerComp>()->SetFirsLvl();

		//going to the game over scene
		SceneManager::GetInstance().SetActiveScene("BurgerTimeGameOver");
	}
	if (event == Event::BURGERS_COMPLETE)
	{
		//resetting the enemies
		m_pEnemyManager->GetComponent<EnemyManagerComp>()->ResetEnemies();
	}
}

void BurgerTimeLvl::ResetScene()
{
	//resetting the level after leaving the scene so we dont see any flickering
	m_pLevel->GetComponent<LevelManagerComp>()->ResetLvl();

	//resetting the score
	m_pScoreCounter->GetComponent<ScoreCounterComp>()->Reset();

	//respawning the player characters
	m_pPeterPepper->GetComponent<EntityMoveComp>()->Respawn();
	m_pPeterPepper->GetComponent<HealthComp>()->Reset();

	//resetting the enemies
	m_pEnemyManager->GetComponent<EnemyManagerComp>()->ResetEnemies();
}