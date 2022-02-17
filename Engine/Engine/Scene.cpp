#include "EnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(GameObject* pGameObj)
{
	m_GameObjs.push_back(pGameObj);
}

void Scene::Initialize()
{
	for (auto& gameObj : m_GameObjs)
	{
		gameObj->Initialize();
	}
}

void Scene::Update()
{
	for(auto& gameObj : m_GameObjs)
	{
		gameObj->Update();
	}

	RemoveDestroyedGameObjs();
}

void Scene::FixedUpdate()
{
	for (auto& gameObj : m_GameObjs)
	{
		gameObj->FixedUpdate();
	}

	RemoveDestroyedGameObjs();
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjs)
	{
		object->Render();
	}
}

void Scene::RemoveDestroyedGameObjs()
{
	auto it = std::remove_if(m_GameObjs.begin(), m_GameObjs.end(), [](GameObject* obj)
		{
			if (obj->IsDestroyed())
				return true;
			return false;
		});

	if (it != m_GameObjs.end())
		m_GameObjs.erase(it, m_GameObjs.end());
}

