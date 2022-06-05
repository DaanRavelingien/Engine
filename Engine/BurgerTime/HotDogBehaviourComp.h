#pragma once
#include <Component.h>

class HitboxComp;

class HotDogBehaviourComp : public Component
{
public:
	HotDogBehaviourComp();
	~HotDogBehaviourComp() = default;
	HotDogBehaviourComp(const HotDogBehaviourComp& other) = delete;
	HotDogBehaviourComp(HotDogBehaviourComp&& other) = delete;
	HotDogBehaviourComp& operator=(const HotDogBehaviourComp& other) = delete;
	HotDogBehaviourComp& operator=(HotDogBehaviourComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void AddTarget(GameObject* pTarget) { m_Targets.push_back(pTarget); };
	void Reset();

private:
	enum class MoveDirection
	{
		Up, Down, Left, Right, None
	};

	MoveDirection m_Direction{MoveDirection::Up};
	HitboxComp* m_pOldPlatform{ nullptr };
	HitboxComp* m_pOldLadder{ nullptr };
	std::vector<GameObject*> m_Targets{};
	int m_TargetIdx{ 0 };

	void SetClosestTarget();
	bool EncounteredNewPlatform();
	bool EncounteredNewLadder();
};

