#include "EnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Logger.h"
#include "ScenePharser.h"

void SceneManager::Initialize()
{
	if (m_pActiveScene)
		m_pActiveScene->Initialize();
	else
		LOGERROR("failed to find an active scene");
}

void SceneManager::Update()
{
	if (m_pActiveScene)
		m_pActiveScene->Update();
	else
		LOGERROR("failed to find an active scene");
}

void SceneManager::FixedUpdate()
{
	if (m_pActiveScene)
		m_pActiveScene->FixedUpdate();
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

void SceneManager::CreateSceneFromJson(const std::string& filePath)
{
	ScenePharser pharser{};
	pharser.CreateScene(filePath);
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
		LOGWARNING("failed to set the given scene as active");
	else //otherwise set as active scene
		m_pActiveScene = *sceneIt;

}
