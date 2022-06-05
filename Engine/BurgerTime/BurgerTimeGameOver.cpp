#include "BurgerTimeGameOver.h"
#include <GameObject.h>
#include <InputManager.h>

//component includes
#include "TextRenderComp.h"
#include "TextComp.h"
#include <TransformComp.h>

void BurgerTimeGameOver::Initialize()
{
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

	GameObject* pHightScoreLable{ new GameObject{ "HightScoreLable" } };
	pHightScoreLable->AddComponent(new TextRenderComp{});
	pHightScoreLable->AddComponent(new TextComp{ "HIGH SCORE", "ArcadeClassic_Size50",{1,0.3f,0.3f} });
	pHightScoreLable->GetTransform()->SetPos({ 0,80,0 });
	pGameOverDispl->AddChild(pHightScoreLable);

	GameObject* pScoreLable{ new GameObject{ "ScoreLable" } };
	pScoreLable->AddComponent(new TextRenderComp{});
	pScoreLable->AddComponent(new TextComp{ "YOUR SCORE", "ArcadeClassic_Size50",{1,0.3f,0.3f} });
	pScoreLable->GetTransform()->SetPos({ 0,120,0 });
	pGameOverDispl->AddChild(pScoreLable);

	AddGameObj(pGameOverDispl);
}

void BurgerTimeGameOver::ContiniuCmd::Execute()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimeMainMenu");
}
