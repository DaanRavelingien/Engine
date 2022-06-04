#include "BurgerTime.h"
#include <ResourceManager.h>

//scenes
#include "BurgerTimeStartMenu.h"
#include "BurgerTimePauseMenu.h"
#include "BurgerTimeLvl.h"
#include "BurgerTimeCoOpLvl.h"
#include "BurgerTimeVsLvl.h"

void BurgerTime::Load() const
{
	//loading the nessecary textures
	ResourceManager::GetInstance().LoadTexture("BurgerTimeTexture", "Textures/BurgerTimeSprites.png");
	ResourceManager::GetInstance().LoadTexture("BurgerTimeLogo", "Textures/BurgerTimeLogo.png");
	
	//loading the nessecary fonts
	ResourceManager::GetInstance().LoadFont("ArcadeClassic_Size30", "Fonts/ARCADECLASSIC.otf", 30);
	ResourceManager::GetInstance().LoadFont("ArcadeClassic_Size50", "Fonts/ARCADECLASSIC.otf", 50);
	ResourceManager::GetInstance().LoadFont("ArcadeClassic_Size100", "Fonts/ARCADECLASSIC.otf", 100);
	
	//creating our main menu scene
	Scene* pMainMenuScene{ new BurgerTimeStartMenu{} };
	SceneManager::GetInstance().AddScene(pMainMenuScene);
	
	//creating our pause menu
	Scene* pPauseMenuScene(new BurgerTimePauseMenu{});
	SceneManager::GetInstance().AddScene(pPauseMenuScene);
	
	//creating our single player scene
	Scene* pBurgerTimeLvl{ new BurgerTimeLvl{} };
	SceneManager::GetInstance().AddScene(pBurgerTimeLvl);

	//creating our CoOp scene
	Scene* pBurgerTimeCoOpLvl{ new BurgerTimeCoOpLvl{} };
	SceneManager::GetInstance().AddScene(pBurgerTimeCoOpLvl);

	//creating our vs scene
	Scene* pBurgerTimeVsLvl{ new BurgerTimeVsLvl{} };
	SceneManager::GetInstance().AddScene(pBurgerTimeVsLvl);
}
