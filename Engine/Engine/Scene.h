#pragma once
#include "SceneManager.h"

class GameObject;

class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(GameObject* pGameObj);

	void Initialize();
	void Update();
	void FixedUpdate();
	void Render() const;
#ifdef _DEBUG
	void RenderGui();
#endif	//_DEBUG
	std::string GetName() const { return m_Name; };

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	explicit Scene(const std::string& name);

	void RemoveDestroyedGameObjs();

	std::string m_Name;
	std::vector <GameObject*> m_GameObjs{};
};


