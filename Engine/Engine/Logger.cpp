#include "EnginePCH.h"
#include "Logger.h"

void Logger::LogWarning(const std::string& message, const char* functionName, int line)
{
	m_WarningCount++;
	std::string outputMessage{ "---Warning(" + std::to_string(m_WarningCount) + "): " + CreateMessage(message, functionName, line) + "---\n"};
	int yellow{ 14 };

	PrintMessage(outputMessage, yellow);
}

void Logger::LogError(const std::string& message, const char* functionName, int line)
{
	m_ErrorCount++;
	std::string outputMessage{ "===ERROR(" + std::to_string(m_ErrorCount) + "): " + CreateMessage(message, functionName, line) + "===\n" };
	int red{ 12 };

	PrintMessage(outputMessage, red);
}

void Logger::LogMessage(const std::string& message, const char* functionName, int line)
{
	m_MessageCount++;
	std::string outputMessage{ "-message(" + std::to_string(m_MessageCount) + "): " + CreateMessage(message, functionName, line) + "-\n" };
	int white{ 15 };

	PrintMessage(outputMessage, white);
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

void Logger::PrintMessage(const std::string& message, int color)
{
	//setting the console color
	SetConsoleTextAttribute(m_ConsoleHandle, WORD(color));
	std::cout << message;
	//setting text back to the defalut console settings
	SetConsoleTextAttribute(m_ConsoleHandle, m_DefaultConsoleInfo.wAttributes);
}
