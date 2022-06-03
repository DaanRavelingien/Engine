#pragma once
#include "Component.h"
#include "Observer.h"

class ScoreCounterComp final : public Component, public Observer<Component>
{
public:
	ScoreCounterComp();
	~ScoreCounterComp() = default;
	ScoreCounterComp(const ScoreCounterComp& other) = delete;
	ScoreCounterComp(ScoreCounterComp&& other) = delete;
	ScoreCounterComp& operator=(const ScoreCounterComp& other) = delete;
	ScoreCounterComp& operator=(ScoreCounterComp&& other) = delete;

	void Initialize() override;
	int GetScore() { return m_Score; };

private:
	int m_Score{};

	void Notify(Component* pComp, Event event) override;
};

