#pragma once
#include <chrono>
#include "Singleton.h"

class Time final : public Singleton<Time>
{
public:
	~Time() = default;

	void Start();
	void Stop();
	void Pause();
	void Continiu();
	void Update();

	float GetDeltaTime() const;
	double GetDeltaTimeAsDouble() const;
	int GetDeltaTimeInMs() const;

protected:
	friend class Singleton<Time>;
	Time() = default;

	bool m_Paused{ false };

	std::chrono::duration<double> m_DeltaTime{};
	std::chrono::steady_clock::time_point m_LastTime{};
};

