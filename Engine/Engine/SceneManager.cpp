#include "EnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Logger.h"

void SceneManager::Update()
{
	if (m_pActiveScene)
		m_pActiveScene->Update();
	else
		Logger::GetInstance().LogError("No active scene found");
}

void SceneManager::FixedUpdate()
{
	//if (m_pActiveScene)
	//	m_pActiveScene->FixedUpdate();
}

void SceneManager::Render()
{
	if (m_pActiveScene)
		m_pActiveScene->Render();
	else
		Logger::GetInstance().LogError("No active scene found");
}

SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		delete pScene;
		pScene = nullptr;
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = new Scene(name);
	m_Scenes.push_back(scene);

	//if no active scene was set set this one
	if (!m_pActiveScene)
		m_pActiveScene = scene;

	return *scene;
}

void SceneManager::SetActiveScene(const std::string& sceneName)
{
	//finding a scene with the name
	auto sceneIt = std::find_if(m_Scenes.begin(), m_Scenes.end(), [sceneName](Scene* pScene)
		{
			if (pScene->GetName() == sceneName)
				return true;
			return false;
		});

	//if no scene was found dont change anything but output an error message
	if (sceneIt == m_Scenes.end())
		Logger::GetInstance().LogError("No scene found with the specified name");
	else //otherwise set as active scene
		m_pActiveScene = *sceneIt;

}
