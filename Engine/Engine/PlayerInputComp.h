#pragma once
#include "Component.h"
#include "Command.h"

class EntityMoveComp;

class PlayerInputComp : public Component
{
public:
	PlayerInputComp();
	~PlayerInputComp() = default;
	PlayerInputComp(const PlayerInputComp& other) = delete;
	PlayerInputComp(PlayerInputComp&& other) = delete;
	PlayerInputComp& operator=(const PlayerInputComp& other) = delete;
	PlayerInputComp& operator=(PlayerInputComp&& other) = delete;

	enum class Direction
	{
		Up, Down, Left, Right, Stand
	};

	void Initialize() override;
	void Update() override;

	void SetMoveDirection(Direction dir) { m_MoveDirection = dir; };

private:
	Direction m_MoveDirection{Direction::Stand};
	EntityMoveComp* m_pEntityMoveComp{ nullptr };
};

class PlayerStartMoveUpCmd : public Command
{
public:
	PlayerStartMoveUpCmd(GameObject* pGameObj) :Command{ pGameObj }{};
	void Execute() override;
};

class PlayerStartMoveDownCmd : public Command
{
public:
	PlayerStartMoveDownCmd(GameObject* pGameObj) :Command{ pGameObj } {};
	void Execute() override;
};

class PlayerStartMoveLeftCmd : public Command
{
public:
	PlayerStartMoveLeftCmd(GameObject* pGameObj) :Command{ pGameObj } {};
	void Execute() override;
};

class PlayerStartMoveRightCmd : public Command
{
public:
	PlayerStartMoveRightCmd(GameObject* pGameObj) :Command{ pGameObj } {};
	void Execute() override;
};

class PlayerStopMoveCmd : public Command
{
public:
	PlayerStopMoveCmd(GameObject* pGameObj) :Command{ pGameObj } {};
	void Execute() override;
};