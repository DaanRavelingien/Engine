#pragma once
#include "Observer.h"

class GameObject;

class Component : public Observer<Component*>
{
public:
	Component();
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Initialize() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};

	virtual void Notify(Component*, Event) override {};

	int GetIdx() const { return m_Idx; };

	void SetGameObj(GameObject* pGameObj) { m_pGameObj = pGameObj; };
	GameObject* GetGameObj() const;

protected:
	GameObject* m_pGameObj{ nullptr };

private:
	static int idxCount;
	int m_Idx{};
};

