#include "EnginePCH.h"
#include "BurgerTimeStartMenu.h"
#include "GameObject.h"
#include "ResourceManager.h"

//component includes
#include "TransformComp.h"
#include "TextureComp.h"
#include "TextureRenderComp.h"
#include "TextComp.h"
#include "TextRenderComp.h"
#include "MenuPointerComp.h"
#include "MenuInputComp.h"
#include "MainMenuManagerComp.h"

void BurgerTimeStartMenu::Initialize()
{
	//creating the burger time logo
	//=============================
	GameObject* pBurgerTimeLogo{ new GameObject{"BurgerTimeLogo"} };
	pBurgerTimeLogo->AddComponent(new TextureRenderComp{});
	pBurgerTimeLogo->AddComponent(new TextureComp{ "Textures/BurgerTimeLogo.png" });

	pBurgerTimeLogo->GetTransform()->SetPos({ 80,50,0 });
	pBurgerTimeLogo->GetTransform()->SetScale({ 0.5f,0.5f,0.5f });
	AddGameObj(pBurgerTimeLogo);

	//creating menu
	//=============

	GameObject* pMenu{ new GameObject{"Menu"} };
	pMenu->AddComponent(new MenuInputComp{});
	pMenu->AddComponent(new MainMenuManagerComp{});

	//single player selection
	//==================================
	GameObject* pSinglePlayerSelection{ new GameObject{"SinglePlayerSelection"} };
	pSinglePlayerSelection->AddComponent(new TextRenderComp{});
	pSinglePlayerSelection->AddComponent(new TextComp{ "1 PLAYER", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pSinglePlayerSelection->GetTransform()->SetPos({0, 0, 0});
	pMenu->AddChild(pSinglePlayerSelection);

	//2 player CoOp selection
	//=======================
	GameObject* pSingleCoOpSelection{ new GameObject{"TwoPlayerCoOpSelection"} };
	pSingleCoOpSelection->AddComponent(new TextRenderComp{});
	pSingleCoOpSelection->AddComponent(new TextComp{ "2 PLAYERS CO OP", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pSingleCoOpSelection->GetTransform()->SetPos({ 0, 40, 0 });
	pMenu->AddChild(pSingleCoOpSelection);

	//2 player VS selection
	//=====================
	GameObject* pVSPlayerSelection{ new GameObject{"TwoPlayerVSSelection"} };
	pVSPlayerSelection->AddComponent(new TextRenderComp{});
	pVSPlayerSelection->AddComponent(new TextComp{ "2 PLAYERS VERSUS", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pVSPlayerSelection->GetTransform()->SetPos({ 0, 80, 0 });
	pMenu->AddChild(pVSPlayerSelection);

	//Options selection
	//=================
	GameObject* pOptionsSelection{ new GameObject{"OptionSelection"} };
	pOptionsSelection->AddComponent(new TextRenderComp{});
	pOptionsSelection->AddComponent(new TextComp{ "OPTIONS", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pOptionsSelection->GetTransform()->SetPos({ 0, 120, 0 });
	pMenu->AddChild(pOptionsSelection);

	//Exit selection
	//==============
	GameObject* pExitSelection{ new GameObject{"ExitSelection"} };
	pExitSelection->AddComponent(new TextRenderComp{});
	pExitSelection->AddComponent(new TextComp{ "EXIT", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pExitSelection->GetTransform()->SetPos({ 0, 160, 0 });
	pMenu->AddChild(pExitSelection);

	//Menu Pointer
	//============
	GameObject* pMenuPointer{ new GameObject{"MenuPointer"} };
	pMenuPointer->AddComponent( new TextureRenderComp{} );
	TextureComp* pTextureComp{ new TextureComp{"Textures/BurgerTimeSprites.png"} };
	pTextureComp->SetSourceRect({ 98,145,8,7 });
	pTextureComp->SetDestRect({ 0,0,8,7 });
	pMenuPointer->AddComponent(pTextureComp);
	pMenuPointer->GetTransform()->SetScale({ 2,2,2 });
	pMenuPointer->AddComponent(new MenuPointerComp{});

	pMenu->AddChild(pMenuPointer);

	pMenu->GetTransform()->SetPos({ 230,300,0 });
	AddGameObj(pMenu);
}

void BurgerTimeStartMenu::Update()
{

}
