#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Engine.h>
#include <ResourceManager.h>
#include "BurgerTime.h"

int main(int, char* [])
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	//create game
	BurgerTime game{};

	//create engine
	Engine engine{};
	engine.Initialize();;

	//load the game
	game.Load();

	//start the engine
	engine.Run();

	return 0;
}