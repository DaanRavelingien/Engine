#include "EnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComp.h"
#include "Render2DComp.h"

GameObject::GameObject(const std::string& name)
	:m_Name{name}
{
	//by default we will always assign a transform component to our game object
	AddComponent(new TransformComp());
} 

TransformComp* GameObject::GetTransform() const
{
	return GetComponent<TransformComp>();
}

GameObject::~GameObject()
{
	for (Component* pComp : m_Components)
	{
		delete pComp;
		pComp = nullptr;
	}
}

void GameObject::Initialize()
{
	for (Component* comp : m_Components)
	{
		comp->Initialize();
	}
}

void GameObject::Update()
{
	if (IsDestroyed())
		return;

	for (Component* comp : m_Components)
	{
		comp->Update();
	}
}

void GameObject::FixedUpdate()
{
	if (IsDestroyed())
		return;

	for (Component* comp : m_Components)
	{
		comp->FixedUpdate();
	}
}

void GameObject::Render() const
{
	//find all the render components of this game object and call the render function on them
	std::for_each(m_Components.begin(), m_Components.end(), [](Component* pComp)
		{
			if (dynamic_cast<Render2DComp*>(pComp) != NULL)
			{
				dynamic_cast<Render2DComp*>(pComp)->Render();
			}
		});
}

void GameObject::AddComponent(Component* pComp)
{
	//setting the component game obj pointer to this
	pComp->SetGameObj(this);

	//subscibing the components observer to this game object
	m_GameObjSubject.AddObserver(pComp);

	m_Components.push_back(pComp);
}

void GameObject::RemoveComponent(int idx)
{
	auto it = std::remove_if(m_Components.begin(), m_Components.end(), [idx](Component* comp)
		{
			if (comp->GetIdx() == idx)
				return true;
			return false;
		});

	if (it == m_Components.end())
		Logger::GetInstance().LogWarning("GameObject.RemoveComponent(int), failed to find component with the specified index");
	else
		m_Components.erase(it, m_Components.end());
}

