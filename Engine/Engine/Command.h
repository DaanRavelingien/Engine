#pragma once
#include "GameObject.h"

class Command
{
public:
	Command(GameObject* pGameObject) :m_pGameObject{ pGameObject } {};
	virtual ~Command() = default;
	virtual void Execute() = 0;

	void Enable() { m_Enabled = true; };
	void Disable() { m_Enabled = false; };
	bool IsEnabled() { return m_Enabled; };

protected:
	GameObject* GetGameObject() const { return m_pGameObject; };
private:
	bool m_Enabled{ true };
	GameObject* m_pGameObject;
};

//example command

//class JumpCommand : public Command
//{
//public:
//	JumpCommand(GameObject* pGameObject) :Command{ pGameObject } {};
//	void Execute() override 
//	{ 
//		//if (GetGameObject()) 
//			//GetGameObject()->Jump();
//	};
//};