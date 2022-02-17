#include "EnginePCH.h"
#include "Engine.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"

//temp includes for the demo scene
//so we can create game obj here
#include "Render2DComp.h"
#include "TextComp.h"
#include "TextureComp.h"
#include "TransformComp.h"
#include "FPSComp.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void Engine::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Game Engine Testing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void Engine::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//background
	GameObject* pGameObj{ new GameObject("Bg") };
	pGameObj->AddComponent(new Render2DComp());
	pGameObj->AddComponent(new TextureComp("background.jpg"));
	scene.Add(pGameObj);

	//logo
	pGameObj = new GameObject("Logo");
	pGameObj->AddComponent(new Render2DComp());
	pGameObj->AddComponent(new TextureComp("logo.png"));
	pGameObj->GetTransform()->SetPos({ 216,180,0 });
	scene.Add(pGameObj);

	//text
	pGameObj = new GameObject("Text");
	pGameObj->AddComponent(new Render2DComp());
	pGameObj->AddComponent(new TextComp("Programming 4 Assignment", "Lingua.otf", 36));
	pGameObj->GetTransform()->SetPos({ 80,20,0 });
	scene.Add(pGameObj);

	//fps counter
	pGameObj = new GameObject("FPS");
	pGameObj->AddComponent(new Render2DComp());
	pGameObj->AddComponent(new TextComp("Programming 4 Assignment", "Lingua.otf", 20, { 0.f,0.8f,0.f }));
	pGameObj->AddComponent(new FPSComp());
	pGameObj->GetTransform()->SetPos({ 10,10,0 });
	scene.Add(pGameObj);
}

void Engine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Engine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.Initialize();	//initialize the current active scene
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	int lag = 0; //lag in Ms

	//starting the game timer
	Time& time{ Time::GetInstance() };
	time.Start();

	while (doContinue)
	{
		Time::GetInstance().Update();
		lag += time.GetDeltaTimeInMs();

		while (lag >= MsPerFrame)
		{
			sceneManager.FixedUpdate();
			lag -= MsPerFrame;
		}

		doContinue = input.ProcessInput();
		sceneManager.Update();
		renderer.Render();
	}

	time.Stop();
	Cleanup();

}
