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
#include "DamageInpComp.h"
#include "TextComp.h"
#include "ScoreCounterComp.h"
#include "ScoreInpComp.h"
#include "TextRenderComp.h"
#include "TextureRenderComp.h"
#include "HitboxManagerComp.h"
#include "HitboxComp.h"
#include "EntityMoveComp.h"

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
	GameObject* pHitboxManager{ new GameObject{"HitboxManager"} };
	HitboxManagerComp* pHitboxManagerComp{ new HitboxManagerComp{} };
	pHitboxManager->AddComponent(pHitboxManagerComp);
	AddGameObj(pHitboxManager);

	//creating a test platform
	//========================
	GameObject* pPlatform{ new GameObject{"Platform"} };
	pPlatform->AddComponent(new HitboxComp{ pHitboxManagerComp,HitboxTag::Platform,28,16 });
	pPlatform->AddComponent(new TextureRenderComp{});
	TextureComp* pPlatformTexture{ new TextureComp{burgerTimeTextureIdx} };
	pPlatformTexture->SetSourceRect({ 114,65,28,6 });
	pPlatformTexture->SetDestRect({ 0,16,28,6 });
	pPlatform->AddComponent(pPlatformTexture);

	pPlatform->GetTransform()->SetPos({ 200,400,0 });
	pPlatform->GetTransform()->SetScale({ 15,3,3 });
	AddGameObj(pPlatform);

	//creating peterPepper
	//====================
	m_pPeterPepper = new GameObject{ "PeterPepper" };
	m_pPeterPepper->AddComponent(new TextureRenderComp{});

	TextureComp* pPeterPepperTextureComp{ new TextureComp{burgerTimeTextureIdx} };
	pPeterPepperTextureComp->SetSourceRect({ 16,0,16,16 });
	pPeterPepperTextureComp->SetDestRect({ 0,0,16,16 });
	m_pPeterPepper->AddComponent(pPeterPepperTextureComp);
	m_pPeterPepper->AddComponent(new HealthComp{ 5 });
	m_pPeterPepper->AddComponent(new DamageInpComp{Controller::Controller_1});
	m_pPeterPepper->AddComponent(new HitboxComp{ pHitboxManagerComp, HitboxTag::Player, 16,16 });
	m_pPeterPepper->AddComponent(new EntityMoveComp{ pPlatform });

	m_pPeterPepper->GetTransform()->SetPos({ 270,250,0 });
	m_pPeterPepper->GetTransform()->SetScale({ 3,3,3 });
	AddGameObj(m_pPeterPepper);

	//creating hud
	//============
	m_pHud = new GameObject{ "Hud" };
	//creating the display for the lives and score of player 1
	GameObject* pLivesDisplay{ new GameObject{"LivesDisplay"} };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pPeterPepper, burgerTimeTextureIdx));
	pLivesDisplay->GetTransform()->SetScale({ 3,3,3 });
	pLivesDisplay->GetTransform()->SetPos({ 20,700,0 });
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
	pScoreCount->AddComponent(new ScoreInpComp{Controller::Controller_1});
	pScoreCount->GetTransform()->SetPos({ 0,40,0 });
	pScoreDisplay->AddChild(pScoreCount);

	pScoreDisplay->GetTransform()->SetPos({ 20,10,0 });
	m_pHud->AddChild(pScoreDisplay);

	AddGameObj(m_pHud);

}

void BurgerTimeLvl::PauseCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimePauseMenu");
}
