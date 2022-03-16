#include "EnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene(const std::string& name) 
	: m_Name(name)
{
}

Scene::~Scene()
{
	for (GameObject* pGameObj : m_GameObjs)
	{
		delete pGameObj;
		pGameObj = nullptr;
	}
}

void Scene::AddGameObj(GameObject* pGameObj)
{
	m_GameObjs.push_back(pGameObj);
}

void Scene::InitializeScene()
{
	//initialize the scene itself
	Initialize();

	for (auto& gameObj : m_GameObjs)
	{
		if(!gameObj->IsDisabled())
			gameObj->Initialize();
	}
}

void Scene::UpdateScene()
{
	//update the scene itself
	Update();

	for(auto& gameObj : m_GameObjs)
	{
		if (!gameObj->IsDisabled())
			gameObj->Update();
	}

	RemoveDestroyedGameObjs();
}

void Scene::FixedUpdateScene()
{
	//update the scene itself
	FixedUpdate();

	for (auto& gameObj : m_GameObjs)
	{
		if (!gameObj->IsDisabled())
			gameObj->FixedUpdate();
	}

	RemoveDestroyedGameObjs();
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjs)
	{
		if(!object->IsDisabled())
			object->Render();
	}
}

#ifdef _DEBUG
void Scene::RenderGui()
{
	for (auto& gameObj : m_GameObjs)
	{
		if(gameObj->IsDisabled())
			gameObj->RenderGui();
	}
}
#endif // _DEBUG

void Scene::RemoveDestroyedGameObjs()
{
	auto it = std::remove_if(m_GameObjs.begin(), m_GameObjs.end(), [](GameObject* obj)
		{
			if (obj->IsDestroyed())
			{
				delete obj;
				obj = nullptr;
				return true;
			}
			return false;
		});

	if (it != m_GameObjs.end())
		m_GameObjs.erase(it, m_GameObjs.end());
}

