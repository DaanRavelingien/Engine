#include "EnginePCH.h"
#include "Time.h"

void Time::Start()
{
	m_Paused = false;
	m_DeltaTime = std::chrono::duration<double>{ 0 };
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void Time::Stop()
{
	m_Paused = true;
	m_DeltaTime = std::chrono::duration<double>{ 0 };
	m_LastTime = std::chrono::high_resolution_clock::time_point();
}

void Time::Pause()
{
	m_Paused = true;
}

void Time::Continiu()
{
	m_Paused = false;
}

void Time::Update()
{
	if (!m_Paused)
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastTime);
		m_LastTime = currentTime;
	}
}

float Time::GetDeltaTime() const
{
	return float(m_DeltaTime.count());
}

double Time::GetDeltaTimeAsDouble() const
{
	return m_DeltaTime.count();
}

int Time::GetDeltaTimeInMs() const
{
	return int(std::chrono::duration_cast<std::chrono::milliseconds>(m_DeltaTime).count());
}
