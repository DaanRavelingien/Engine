#pragma once
#include "GameObject.h"

class Command
{
public:
	Command(GameObject* pGameObject) :m_pGameObject{ pGameObject } {};
	virtual ~Command() = default;
	virtual void Execute() = 0;
protected:
	GameObject* GetGameObject() const { return m_pGameObject; };
private:
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