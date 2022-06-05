#include "EnginePCH.h"
#include "BurgerTimeStartMenu.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SoundSystem.h"
#include "BurgerTimeData.h"

//component includes
#include "TransformComp.h"
#include "TextureComp.h"
#include "TextureRenderComp.h"
#include "TextComp.h"
#include "TextRenderComp.h"
#include "MenuInputComp.h"
#include "MenuComp.h"
#include "MenuSelectionExitComp.h"
#include "MenuSelectionStartComp.h"
#include "MenuSelectionCompCoOpStart.h"
#include "MenuSelectionVsStartComp.h"

void BurgerTimeStartMenu::Initialize()
{
	//loading the sound for the menu
	//==============================
	GetSoundSystem()->LoadSound("MainMenuBg", "../Data/Sound/BgMainMenu.wav", true);

	//creating the burger time logo
	//=============================
	GameObject* pBurgerTimeLogo{ new GameObject{"BurgerTimeLogo"} };
	pBurgerTimeLogo->AddComponent(new TextureRenderComp{});
	pBurgerTimeLogo->AddComponent(new TextureComp{ "BurgerTimeLogo" });

	pBurgerTimeLogo->GetTransform()->SetPos({ 80,50,0 });
	pBurgerTimeLogo->GetTransform()->SetScale({ 0.5f,0.5f,0.5f });
	AddGameObj(pBurgerTimeLogo);

	//creating menu
	//=============
	GameObject* pMenu{ new GameObject{"Menu"} };
	pMenu->AddComponent(new MenuInputComp{});
	pMenu->AddComponent(new MenuComp{});
	pMenu->AddComponent(new TextureRenderComp{});
	TextureComp* pTextureComp{ new TextureComp{"BurgerTimeTexture"} };
	pTextureComp->SetSourceRect({ 0,144,8,7 });
	pTextureComp->SetDestRect({ 0,0,16,14 });
	pMenu->AddComponent(pTextureComp);

	//single player selection
	//==================================
	GameObject* pSinglePlayerSelection{ new GameObject{"SinglePlayerSelection"} };
	pSinglePlayerSelection->AddComponent(new MenuSelectionStartComp{});
	pSinglePlayerSelection->AddComponent(new TextRenderComp{});
	pSinglePlayerSelection->AddComponent(new TextComp{ "1 PLAYER", "ArcadeClassic_Size30",{1,1,1} });
	pSinglePlayerSelection->GetTransform()->SetPos({0, 0, 0});
	pMenu->AddChild(pSinglePlayerSelection);

	//2 player CoOp selection
	//=======================
	GameObject* pCoOpSelection{ new GameObject{"TwoPlayerCoOpSelection"} };
	pCoOpSelection->AddComponent(new MenuSelectionCompCoOpStart{});
	pCoOpSelection->AddComponent(new TextRenderComp{});
	pCoOpSelection->AddComponent(new TextComp{ "2 PLAYERS CO OP", "ArcadeClassic_Size30",{1,1,1} });
	pCoOpSelection->GetTransform()->SetPos({ 0, 40, 0 });
	pMenu->AddChild(pCoOpSelection);

	//2 player VS selection
	//=====================
	GameObject* pVSPlayerSelection{ new GameObject{"TwoPlayerVSSelection"} };
	pVSPlayerSelection->AddComponent(new MenuSelectionVsStartComp{});
	pVSPlayerSelection->AddComponent(new TextRenderComp{});
	pVSPlayerSelection->AddComponent(new TextComp{ "2 PLAYERS VERSUS", "ArcadeClassic_Size30",{1,1,1} });
	pVSPlayerSelection->GetTransform()->SetPos({ 0, 80, 0 });
	pMenu->AddChild(pVSPlayerSelection);

	//Exit selection
	//==============
	GameObject* pExitSelection{ new GameObject{"ExitSelection"} };
	pExitSelection->AddComponent(new MenuSelectionExitComp{});
	pExitSelection->AddComponent(new TextRenderComp{});
	pExitSelection->AddComponent(new TextComp{ "EXIT", "ArcadeClassic_Size30",{1,1,1} });
	pExitSelection->GetTransform()->SetPos({ 0, 120, 0 });
	pMenu->AddChild(pExitSelection);

	pMenu->GetTransform()->SetPos({ 230,300,0 });
	AddGameObj(pMenu);
}

void BurgerTimeStartMenu::OnSceneActivated()
{
	//start playing music
	GetSoundSystem()->ContiniuMusic();
	GetSoundSystem()->PlayMusic("MainMenuBg", (float)BurgerTimeData::GetInstance().GetGameVolume());
}

void BurgerTimeStartMenu::OnSceneDeactivated()
{
	//stop playing music
	GetSoundSystem()->PauseMusic();
}
