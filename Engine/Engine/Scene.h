#pragma once
#include "SceneManager.h"
#include "Subject.h"

class GameObject;
class InputManager;
class Component;
class SoundSystem;

class Scene
{
public:
	void InitializeScene();
	void UpdateScene();
	void FixedUpdateScene();
	bool ProcessInput();
	void Render() const;
#ifdef _DEBUG
	void RenderGui();
#endif	//_DEBUG
	std::string GetName() const { return m_Name; };
	std::vector<GameObject*> GetGameObjects() const { return m_GameObjs; };

	void AddGameObj(GameObject* pGameObj);

	bool IsInitialized() const { return m_Initialized; };
	InputManager* GetInputManager() const { return m_pInputManager; };
	SoundSystem* GetSoundSystem() const { return m_pSoundSystem; };

	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	void AddObserver(Observer<Component>* pObserver) { m_SceneSubject.AddObserver(pObserver); };
	void SendNotification(Component* pComp, Event event) { m_SceneSubject.Notify(pComp, event); };

protected:
	virtual void Update() {};
	virtual void Initialize() {};
	virtual void FixedUpdate() {};

	explicit Scene(const std::string& name);
private: 
	std::vector <GameObject*> m_GameObjs{};
	std::vector <GameObject*> m_ObjsToAdd{};
	std::string m_Name;
	InputManager* m_pInputManager{ nullptr };
	SoundSystem* m_pSoundSystem{ nullptr };

	bool m_Initialized{ false };

	Subject<Component> m_SceneSubject{};

	void AddNewGameObjs();
	void RemoveDestroyedGameObjs();
};


