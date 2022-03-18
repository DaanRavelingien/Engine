#pragma once
#include "SceneManager.h"

class GameObject;

class Scene
{
public:
	void InitializeScene();
	void UpdateScene();
	void FixedUpdateScene();
	void Render() const;
#ifdef _DEBUG
	void RenderGui();
#endif	//_DEBUG
	std::string GetName() const { return m_Name; };
	std::vector<GameObject*> GetGameObjects() const { return m_GameObjs; };

	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

protected:
	virtual void Update() {};
	virtual void Initialize() {};
	virtual void FixedUpdate() {};

	explicit Scene(const std::string& name);
	void AddGameObj(GameObject* pGameObj);
private: 
	std::vector <GameObject*> m_GameObjs{};
	std::string m_Name;

	void RemoveDestroyedGameObjs();
};


