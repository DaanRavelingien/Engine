#include "EnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SoundSystem.h"
#include "TransformComp.h"

Scene::Scene(const std::string& name) 
	: m_Name(name)
{
	//create the input manager
	m_pInputManager = new InputManager{};

	m_pSoundSystem = new SdlSoundSystem{};
}

Scene::~Scene()
{
	for (GameObject* pGameObj : m_GameObjs)
	{
		delete pGameObj;
		pGameObj = nullptr;
	}

	for (GameObject* pGameObj : m_ObjsToAdd)
	{
		delete pGameObj;
		pGameObj = nullptr;
	}

	delete m_pInputManager;
	m_pInputManager = nullptr;

	delete m_pSoundSystem;
	m_pSoundSystem = nullptr;
}

void Scene::AddGameObj(GameObject* pGameObj)
{
	//adding the children to the scene
	for (GameObject* pChild : pGameObj->GetChildren())
	{
		AddGameObj(pChild);
	}

	pGameObj->SetScene(this);
	m_ObjsToAdd.push_back(pGameObj);
}

void Scene::InitializeScene()
{
	//initialize the scene itself
	Initialize();
	m_Initialized = true;

	//add all added objects
	AddNewGameObjs();

	for (auto& gameObj : m_GameObjs)
	{
		if (!gameObj->IsDisabled())
		{
			gameObj->Initialize();
			gameObj->SetInitialized(true);
		}
	}
}

void Scene::UpdateScene()
{
	//update the scene itself
	Update();

	//add all newly added game objects
	AddNewGameObjs();

	for (GameObject* pGameObj : m_GameObjs)
	{
		if (!pGameObj->IsDisabled())
		{
			//initialize the newly added game objects
			if(!pGameObj->IsInitialized())
			{
				pGameObj->Initialize();
				pGameObj->SetInitialized(true);
			}
			pGameObj->Update();
		}
	}

	RemoveDestroyedGameObjs();
}

//cannot add game objects in the fixed update only in initialize and update
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

bool Scene::ProcessInput()
{
	return m_pInputManager->ProcessInput();
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

void Scene::AddNewGameObjs()
{
	if (m_ObjsToAdd.size() > 0)
	{

		for (GameObject* pObj : m_ObjsToAdd)
		{
			m_GameObjs.push_back(pObj);
		}

		//order the new game objects from closest z distance to furthest
		//so they are rendered correctly
		std::sort(m_GameObjs.begin(), m_GameObjs.end(), [](GameObject* pGameObj, GameObject* pOtherGameObj)
			{
				if (pGameObj->GetTransform()->GetPos().z < pOtherGameObj->GetTransform()->GetPos().z)
					return true;
				return false;
			});

		m_ObjsToAdd.clear();
	}
}

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
