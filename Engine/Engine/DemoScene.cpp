#include "EnginePCH.h"
#include "DemoScene.h"
#include "GameObject.h"
#include "TextComp.h"
#include "FPSComp.h"
#include "TextureComp.h"
#include "SpriteComp.h"
#include "TransformComp.h"
#include "TextRenderComp.h"
#include "TextureRenderComp.h"

DemoScene::DemoScene()
	:Scene("DemoScene")
{
}

void DemoScene::Initialize()
{
	//creating the fps game object
	GameObject* pFpsObj{ new GameObject{"FPS"}};
	pFpsObj->AddComponent(new TextRenderComp{});
	pFpsObj->AddComponent(new TextComp{ "0","Fonts/Lingua.otf",20,{0,0.8f,0} });
	pFpsObj->AddComponent(new FPSComp{});

	pFpsObj->GetTransform()->SetPos({ 10,10,0 });
	AddGameObj(pFpsObj);

	//creating the sprite game object
	GameObject* pSpriteObj{ new GameObject{"SpriteObj"} };
	pSpriteObj->AddComponent(new TextureRenderComp{});
	pSpriteObj->AddComponent(new TextureComp{ "Textures/TestSprite.png" });
	pSpriteObj->AddComponent(new SpriteComp{ 29,{40,44},{0,0},0.1f });

	pSpriteObj->GetTransform()->SetPos({ 270,250,0 });
	pSpriteObj->GetTransform()->SetScale({ 4,4,4 });
	AddGameObj(pSpriteObj);
}
