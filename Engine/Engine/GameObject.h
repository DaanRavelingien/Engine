#pragma once
#include "Component.h"
#include "Subject.h"
#include <string>

class TransformComp;
class Scene;

class GameObject final
{
public:
	GameObject(const std::string& name);
	virtual ~GameObject();
	GameObject(const GameObject & other) = delete;
	GameObject(GameObject && other) = delete;
	GameObject& operator=(const GameObject & other) = delete;
	GameObject& operator=(GameObject && other) = delete;

	void Initialize();
	void Update();
	void FixedUpdate();
	void Render() const;
#ifdef _DEBUG
	void RenderGui();
#endif // _DEBUG
	void SetScene(Scene* pScene) { m_pScene = pScene; };
	Scene* GetScene() const { return m_pScene; };

	void Destroy() { m_Destroyed = true; };
	bool IsDestroyed() const { return m_Destroyed; };

	void Enable() { m_Disabled = false; };
	void Disable() { m_Disabled = true; };
	bool IsDisabled() const { return m_Disabled; };

	bool IsInitialized() const { return m_Initialized; };
	void SetInitialized(bool initialized) { m_Initialized = initialized; };

	std::string GetName() const { return m_Name; };
	void Rename(const std::string& name) { m_Name = name; };

	void AddChild(GameObject* pGameObj);
	std::vector<GameObject*> GetChildren() const { return m_Children; };
	void SetParent(GameObject* pGameObj);
	GameObject* GetParent() const { return m_pParent; };

	void AddComponent(Component* comp);
	void RemoveComponent(int idx);

	void AddObserver(Observer<Component>* pObserver);

	//removes all components of given type
	template<typename T>
	void RemoveComponents()
	{
		auto it = std::remove_if(m_Components.begin(), m_Components.end(), [](Component* pComponent)
			{
				if (dynamic_cast<T*>(pComponent))
				{
					delete pComponent;
					pComponent = nullptr;
					return true;
				}
				return false;
			});

		if (it == m_Components.end)
			Logger::GetInstance().LogWarning("GameObject.RemoveComponents(), No components of type were found");
		else
			m_Components.erase(it, m_Components.end());
	}
	//only gets the first added comp of given type
	template<typename T>
	T* GetComponent() const
	{
		auto it = std::find_if(m_Components.begin(), m_Components.end(), [](Component* pComponent)
			{
				if (dynamic_cast<T*>(pComponent))
					return true;
				return false;
			});

		if (it == m_Components.end())
		{
			LOGWARNING("Could Not find a component of given type");
			return nullptr;
		}

		return dynamic_cast<T*>(*it);
	};
	//gets the comp of type with idx for if you want a specific comp
	template<typename T>
	T* GetComponent(int idx) const
	{
		auto it = std::find_if(m_Components.begin(), m_Components.end(), [idx](Component* pComponent)
			{
				if (dynamic_cast<T*>(pComponent) && pComponent->GetIdx() == idx)
					return true;
				return false;
			});

		if (it == m_Components.end())
		{
			LOGWARNING("Could Not find a component of given type with given index");
			return nullptr;
		}

		return dynamic_cast<T*>(*it);
	};

	//some functions for easier acces to the default transform component
	TransformComp* GetTransform() const;

	//add some functions to send notifications to other components
	void SendNotification(Component* pComp, Event event) { m_GameObjSubject.Notify(pComp, event); };

private:
	std::string m_Name{};
	std::vector<Component*> m_Components{};
	GameObject* m_pParent{ nullptr };
	std::vector<GameObject*> m_Children{};
	bool m_Destroyed{ false };
	bool m_Disabled{ false };
	bool m_Initialized{ false };
	Scene* m_pScene{ nullptr };

	//add subject to the game object so it can send events to all its components
	//with as payload the component
	Subject<Component> m_GameObjSubject{};
};

