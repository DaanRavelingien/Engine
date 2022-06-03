#include "EnginePCH.h"
#include "Time.h"

void GameTime::Start()
{
	m_Paused = false;
	m_DeltaTime = std::chrono::duration<double>{ 0 };
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void GameTime::Stop()
{
	m_Paused = true;
	m_DeltaTime = std::chrono::duration<double>{ 0 };
	m_LastTime = std::chrono::high_resolution_clock::time_point();
}

void GameTime::Pause()
{
	m_Paused = true;
}

void GameTime::Continiu()
{
	m_Paused = false;
}

void GameTime::Update()
{
	if (!m_Paused)
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastTime);
		m_LastTime = currentTime;
	}
}

float GameTime::GetDeltaTime() const
{
	return float(m_DeltaTime.count());
}

double GameTime::GetDeltaTimeAsDouble() const
{
	return m_DeltaTime.count();
}

int GameTime::GetDeltaTimeInMs() const
{
	return int(std::chrono::duration_cast<std::chrono::milliseconds>(m_DeltaTime).count());
}
