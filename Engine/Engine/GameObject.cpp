#include "EnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComp.h"
#include "TextureRenderComp.h"
#include "TextRenderComp.h"
#include "Scene.h"

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
	if (IsDestroyed())
		return;

	for (Component* comp : m_Components)
	{
		if(comp->IsEnabled())
			comp->Initialize();
	}
}

void GameObject::Update()
{
	if (IsDestroyed() || m_Disabled)
		return;

	for (Component* comp : m_Components)
	{
		if (comp->IsEnabled())
			comp->Update();
	}
}

void GameObject::FixedUpdate()
{
	if (IsDestroyed() || m_Disabled)
		return;

	for (Component* comp : m_Components)
	{
		if (comp->IsEnabled())
			comp->FixedUpdate();
	}
}

void GameObject::Render() const
{
	if (IsDestroyed() || m_Disabled)
		return;

	//find all the render components of this game object and call the render function on them
	std::for_each(m_Components.begin(), m_Components.end(), [](Component* pComp)
		{
			if (dynamic_cast<TextureRenderComp*>(pComp) != NULL)
			{
				dynamic_cast<TextureRenderComp*>(pComp)->Render();
			}
			if (dynamic_cast<TextRenderComp*>(pComp) != NULL)
			{
				dynamic_cast<TextRenderComp*>(pComp)->Render();
			}
		});
}

#ifdef _DEBUG
void GameObject::RenderGui()
{
	if (IsDestroyed() || m_Disabled)
		return;

	for (Component* comp : m_Components)
	{
		if (comp->IsEnabled())
			comp->RenderGui();
	}
}
#endif // _DEBUG

void GameObject::Destroy()
{
	m_Destroyed = true;

	//also destroying the children
	for (GameObject* pChild : this->GetChildren())
	{
		pChild->Destroy();
	}
}

void GameObject::Enable()
{
	m_Disabled = false;

	//doing the same for the children
	for (GameObject* pChild : this->GetChildren())
	{
		pChild->Enable();
	}
}

void GameObject::Disable()
{
	m_Disabled = true;

	//doing the same for the children
	for (GameObject* pChild : this->GetChildren())
	{
		pChild->Disable();
	}
}

void GameObject::AddChild(GameObject* pGameObj)
{
	if (IsDestroyed())
		return;

	//checking if the gameObj is already a child to avoid adding a game obj twice
	auto it = std::find_if(m_Children.begin(), m_Children.end(), [pGameObj](GameObject* pOtherGameObj)
		{
			if (pGameObj->GetName() == pOtherGameObj->GetName())
				return true;
			return false;
		});

	//only adding if it was not yet added to the vector
	if (it == m_Children.end())
	{
		m_Children.push_back(pGameObj);
		pGameObj->SetParent(this);
	}
}

std::vector<GameObject*> GameObject::GetChildren() const
{
	return m_Children;
}

void GameObject::RemoveChild(GameObject* pGameObj)
{
	if (IsDestroyed())
		return;

	auto it = std::remove(m_Children.begin(), m_Children.end(), pGameObj);
	m_Children.erase(it, m_Children.end());
}

void GameObject::SetParent(GameObject* pGameObj)
{
	if (IsDestroyed())
		return;

	if (m_pParent != pGameObj)
	{
		pGameObj->AddChild(this);
		m_pParent = pGameObj;
	}
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

void GameObject::AddComponent(Component* pComp)
{
	if (IsDestroyed())
		return;

	//setting the component game obj pointer to this
	pComp->SetGameObj(this);

	m_Components.push_back(pComp);
}

void GameObject::RemoveComponent(int idx)
{
	if (IsDestroyed())
		return;

	auto it = std::remove_if(m_Components.begin(), m_Components.end(), [idx](Component* comp)
		{
			if (comp->GetIdx() == idx)
				return true;
			return false;
		});

	if (it == m_Components.end())
		LOGWARNING("failed to find component with the specified index");
	else
		m_Components.erase(it, m_Components.end());
}

void GameObject::AddObserver(Observer<Component>* pObserver)
{
	if (IsDestroyed())
		return;

	m_GameObjSubject.AddObserver(pObserver);
}