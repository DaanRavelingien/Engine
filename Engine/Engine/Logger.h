#pragma once
#include "Singleton.h"
#include <windows.h>

class Logger final : public Singleton<Logger>
{
public:
	void LogWarning(const std::string& message);
	void LogError(const std::string& message);
	void LogMessage(const std::string& message);

protected:
	friend class Singleton<Logger>;
	Logger();

	HANDLE m_ConsoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) };
	CONSOLE_SCREEN_BUFFER_INFO  m_DefaultConsoleInfo{};
};

