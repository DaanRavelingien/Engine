#include "EnginePCH.h"
#include "Logger.h"

void Logger::LogWarning(const std::string& message, const char* functionName, int line)
{
	//setting the console color to yellow
	SetConsoleTextAttribute(m_ConsoleHandle, 14);
	std::cout << "---Warning: " + CreateMessage(message, functionName, line) << "---\n";
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}

void Logger::LogError(const std::string& message, const char* functionName, int line)
{
	//setting the console color to red
	SetConsoleTextAttribute(m_ConsoleHandle, 12);
	std::cout << "---ERROR: " + CreateMessage(message, functionName, line) << "---\n";
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}

void Logger::LogMessage(const std::string& message, const char* functionName, int line)
{
	//setting the console color to white
	SetConsoleTextAttribute(m_ConsoleHandle, 15);
	std::cout << "---message: " + CreateMessage(message, functionName, line) << "---\n";
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}

Logger::Logger()
	:m_ConsoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
	GetConsoleScreenBufferInfo(m_ConsoleHandle, &m_DefaultConsoleInfo);
}

std::string Logger::CreateMessage(const std::string& message, const char* functionName, int line)
{
	//example
	//---Warning: Class::FuncionName(), ln:22, msg: here should appear a message---
	return std::string{ functionName } + "(), ln:" + std::to_string(line) + ", msg: " + message;
}
