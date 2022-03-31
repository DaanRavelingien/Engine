#include "EnginePCH.h"
#include "BurgerTimeLvl.h"
#include "GameObject.h"
#include "glm\detail\type_vec4.hpp"
#include "ResourceManager.h"
#include "InputManager.h"

//component includes
#include "TextureComp.h"
#include "TransformComp.h"
#include "LivesDisplayComp.h"
#include "HealthComp.h"
#include "TextComp.h"
#include "ScoreCounterComp.h"
#include "TextRenderComp.h"
#include "TextureRenderComp.h"
#include "HitboxManagerComp.h"
#include "HitboxComp.h"
#include "EntityMoveComp.h"
#include "PlayerInputComp.h"
#include "LevelLoaderComp.h"

void BurgerTimeLvl::Initialize()
{
	//setting the input controller amount to 2
	GetInputManager()->SetControllerAmount(2);

	//setting some general inputs like pausing the game
	GetInputManager()->SetCommand(KeyboardButton::ESC, ButtonState::Up, new PauseCmd{nullptr});
	GetInputManager()->SetCommand(ControllerButton::StartButton, ButtonState::Up, new PauseCmd{ nullptr }, Controller::Controller_1);
	GetInputManager()->SetCommand(ControllerButton::BackButton, ButtonState::Up, new PauseCmd{ nullptr }, Controller::Controller_1);

	//loading the burgertime texture with all the sprites
	int burgerTimeTextureIdx = ResourceManager::GetInstance().LoadTexture("Textures/BurgerTimeSprites.png");

	//creating a hitbox manager object
	//================================
	m_pHitboxManager = new GameObject{"HitboxManager"};
	HitboxManagerComp* pHitboxManagerComp{ new HitboxManagerComp{} };
	m_pHitboxManager->AddComponent(pHitboxManagerComp);
	AddGameObj(m_pHitboxManager);

	//creating peterPepper
	//====================
	m_pPeterPepper = new GameObject{ "PeterPepper" };
	m_pPeterPepper->AddComponent(new TextureRenderComp{});

	TextureComp* pPeterPepperTextureComp{ new TextureComp{burgerTimeTextureIdx} };
	pPeterPepperTextureComp->SetSourceRect({ 16,0,16,16 });
	pPeterPepperTextureComp->SetDestRect({ 0,0,16,16 });
	m_pPeterPepper->AddComponent(pPeterPepperTextureComp);
	m_pPeterPepper->AddComponent(new HealthComp{ 5 });
	m_pPeterPepper->AddComponent(new HitboxComp{HitboxTag::Player, 16,16 });
	m_pPeterPepper->AddComponent(new EntityMoveComp{});
	m_pPeterPepper->AddComponent(new PlayerInputComp{});

	m_pPeterPepper->GetTransform()->SetPos({ 200,400,0 });
	m_pPeterPepper->GetTransform()->SetScale({ 3,3,3 });
	AddGameObj(m_pPeterPepper);

	//creating hud
	//============
	m_pHud = new GameObject{ "Hud" };
	//creating the display for the lives and score of player 1
	GameObject* pLivesDisplay{ new GameObject{"LivesDisplay"} };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pPeterPepper, burgerTimeTextureIdx));

	pLivesDisplay->GetTransform()->SetScale({ 3,3,3 });
	pLivesDisplay->GetTransform()->SetPos({ 10,700,0 });
	m_pHud->AddChild(pLivesDisplay);

	GameObject* pScoreDisplay{ new GameObject{ "ScoreDisplay" } };

	GameObject* pScoreLabel{ new GameObject{ "ScoreLabel" } };
	pScoreLabel->AddComponent(new TextRenderComp{});
	pScoreLabel->AddComponent(new TextComp{ "SCORE P1", "Fonts/ARCADECLASSIC.otf", 50,{1,0,0} });
	pScoreLabel->GetTransform()->SetPos({ 0,0,0 });
	pScoreDisplay->AddChild(pScoreLabel);

	GameObject* pScoreCount{ new GameObject{"ScoreCount"} };
	pScoreCount->AddComponent(new TextRenderComp);
	pScoreCount->AddComponent(new TextComp{ "0", "Fonts/ARCADECLASSIC.otf", 50, {1,1,1} });
	pScoreCount->AddComponent(new ScoreCounterComp{});
	pScoreCount->GetTransform()->SetPos({ 0,40,0 });
	pScoreDisplay->AddChild(pScoreCount);

	pScoreDisplay->GetTransform()->SetPos({ 20,10,0 });
	m_pHud->AddChild(pScoreDisplay);

	AddGameObj(m_pHud);

	//creating the level from a json
	//==============================
	GameObject* pLevel{ new GameObject{"Level"} };
	pLevel->AddComponent(new LevelLoaderComp{ "../Data/Levels/Level1.json" });
	pLevel->GetTransform()->SetScale({ 3,3,3 });
	pLevel->GetTransform()->SetPos({ 48,60,-1 });
	AddGameObj(pLevel);
}

void BurgerTimeLvl::PauseCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimePauseMenu");
}
