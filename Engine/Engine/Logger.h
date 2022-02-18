#pragma once
#include "Singleton.h"
#include <Windows.h>

class Logger final : public Singleton<Logger>
{
public:
	void LogWarning(const std::string& message, const char* functionName, int line);
	void LogError(const std::string& message, const char* functionName, int line);
	void LogMessage(const std::string& message, const char* functionName, int line);

protected:
	friend class Singleton<Logger>;
	
private:
	Logger();
	std::string CreateMessage(const std::string& message, const char* functionName, int line);
	void PrintMessage(const std::string& message, int color);

	HANDLE m_ConsoleHandle{};
	CONSOLE_SCREEN_BUFFER_INFO  m_DefaultConsoleInfo{};
	int m_ErrorCount{ 0 };
	int m_WarningCount{ 0 };
	int m_MessageCount{ 0 };
};

#define LOGERROR(message) Logger::GetInstance().LogError(message, __FUNCTION__, __LINE__)
#define LOGWARNING(message) Logger::GetInstance().LogWarning(message, __FUNCTION__, __LINE__)
#define LOGMESSAGE(message) Logger::GetInstance().LogMessage(message, __FUNCTION__, __LINE__)

