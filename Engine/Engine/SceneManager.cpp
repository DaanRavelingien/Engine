#include "EnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Logger.h"

void SceneManager::Initialize()
{
	if (m_pActiveScene)
		m_pActiveScene->InitializeScene();
	else
		LOGERROR("failed to find an active scene");
}

void SceneManager::Update()
{
	if (m_pActiveScene)
		m_pActiveScene->UpdateScene();
	else
		LOGERROR("failed to find an active scene");
}

void SceneManager::FixedUpdate()
{
	if (m_pActiveScene)
		m_pActiveScene->FixedUpdateScene();
	else
		LOGERROR("failed to find an active scene");
}

void SceneManager::Render()
{
	if (m_pActiveScene)
		m_pActiveScene->Render();
	else
		LOGERROR("failed to find an active scene");
}

#ifdef _DEBUG
void SceneManager::RenderGui()
{
	if (m_pActiveScene)
		m_pActiveScene->RenderGui();
	else
		LOGERROR("failed to find an active scene");
}
#endif // _DEBUG

SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		delete pScene;
		pScene = nullptr;
	}
}

Scene& SceneManager::AddScene(Scene* pScene)
{
	m_Scenes.push_back(pScene);

	//if no active scene was set set this one
	if (!m_pActiveScene)
		m_pActiveScene = pScene;

	return *pScene;
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
		LOGWARNING("failed to set the given scene as active");
	else //otherwise set as active scene
	{
		if (!(*sceneIt)->IsInitialized())
			(*sceneIt)->InitializeScene();

		m_pActiveScene = *sceneIt;
	}

}
