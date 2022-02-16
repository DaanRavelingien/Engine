#include "EnginePCH.h"
#include "Logger.h"

void Logger::LogWarning(const std::string& message)
{
	//setting the console color to yellow
	SetConsoleTextAttribute(m_ConsoleHandle, 14);
	std::cout << "Warning: " << message << "\n";
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}

void Logger::LogError(const std::string& message)
{
	//setting the console color to red
	SetConsoleTextAttribute(m_ConsoleHandle, 12);
	std::cout << "Error: " << message << "\n";
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}

void Logger::LogMessage(const std::string& message)
{
	//setting the console color to white
	SetConsoleTextAttribute(m_ConsoleHandle, 15);
	std::cout << "Message: " << message << "\n";
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}

Logger::Logger()
{
	GetConsoleScreenBufferInfo(m_ConsoleHandle, &m_DefaultConsoleInfo);
}
