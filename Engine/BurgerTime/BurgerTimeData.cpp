#include "EnginePCH.h"
#include "BurgerTimeData.h"
#include <fstream>
#include <iostream>
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

int BurgerTimeData::GetHeighScore(GameMode gameMode)
{
	std::string data{ GetDataSring() };

	//getting the string into a rapidjson document
	rapidjson::Document jsonData{};
	jsonData.Parse(data.c_str());

	if (!jsonData.IsObject())
	{
		LOGERROR("Failed to pharse the scene file: " + m_SourcePath);
		return 0;
	}

	switch (gameMode)
	{
	case BurgerTimeData::GameMode::Single:
		return jsonData["HighScores"]["SinglePlayer"].GetInt();
		break;
	case BurgerTimeData::GameMode::CoOp:
		return jsonData["HighScores"]["CoOp"].GetInt();
		break;
	case BurgerTimeData::GameMode::Vs:
		return jsonData["HighScores"]["Versus"].GetInt();
		break;
	default:
		break;
	}

	return 0;
}

int BurgerTimeData::GetScore(GameMode gameMode)
{
	std::string data{ GetDataSring() };

	//getting the string into a rapidjson document
	rapidjson::Document jsonData{};
	jsonData.Parse(data.c_str());

	if (!jsonData.IsObject())
	{
		LOGERROR("Failed to pharse the scene file: " + m_SourcePath);
		return 0;
	}

	switch (gameMode)
	{
	case BurgerTimeData::GameMode::Single:
		return jsonData["Scores"]["SinglePlayer"].GetInt();
		break;
	case BurgerTimeData::GameMode::CoOp:
		return jsonData["Scores"]["CoOp"].GetInt();
		break;
	case BurgerTimeData::GameMode::Vs:
		return jsonData["Scores"]["Versus"].GetInt();
		break;
	default:
		break;
	}

	return 0;
}

void BurgerTimeData::SetHeighScore(GameMode gameMode, int score)
{
	std::string data{ GetDataSring() };

	//getting the string into a rapidjson document
	rapidjson::Document jsonData{};
	jsonData.Parse(data.c_str());

	if (!jsonData.IsObject())
	{
		LOGERROR("Failed to pharse the scene file: " + m_SourcePath);
		return;
	}

	switch (gameMode)
	{
	case BurgerTimeData::GameMode::Single:
		jsonData["HighScores"]["SinglePlayer"].SetInt(score);
		break;
	case BurgerTimeData::GameMode::CoOp:
		jsonData["HighScores"]["CoOp"].SetInt(score);
		break;
	case BurgerTimeData::GameMode::Vs:
		jsonData["HighScores"]["Versus"].SetInt(score);
		break;
	default:
		break;
	}

	//writing the data back to the data file
	rapidjson::StringBuffer buffer;

	buffer.Clear();

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	jsonData.Accept(writer);

	std::ofstream outStream{};
	outStream.open(m_SourcePath);
	outStream << buffer.GetString();
	outStream.close();
}

void BurgerTimeData::SetScore(GameMode gameMode, int score)
{
	std::string data{ GetDataSring() };

	//getting the string into a rapidjson document
	rapidjson::Document jsonData{};
	jsonData.Parse(data.c_str());

	if (!jsonData.IsObject())
	{
		LOGERROR("Failed to pharse the scene file: " + m_SourcePath);
		return;
	}

	switch (gameMode)
	{
	case BurgerTimeData::GameMode::Single:
		jsonData["Scores"]["SinglePlayer"].SetInt(score);
		break;
	case BurgerTimeData::GameMode::CoOp:
		jsonData["Scores"]["CoOp"].SetInt(score);
		break;
	case BurgerTimeData::GameMode::Vs:
		jsonData["Scores"]["Versus"].SetInt(score);
		break;
	default:
		break;
	}

	//writing the data back to the data file
	rapidjson::StringBuffer buffer;

	buffer.Clear();

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	jsonData.Accept(writer);

	std::ofstream outStream{};
	outStream.open(m_SourcePath);
	outStream << buffer.GetString();
	outStream.close();
}

int BurgerTimeData::GetGameVolume()
{
	std::string data{ GetDataSring() };

	//getting the string into a rapidjson document
	rapidjson::Document jsonData{};
	jsonData.Parse(data.c_str());

	if (!jsonData.IsObject())
	{
		LOGERROR("Failed to pharse the scene file: " + m_SourcePath);
		return 0;
	}

	return jsonData["Sound"]["Volume"].GetInt();
}

std::string BurgerTimeData::GetDataSring()
{
	//getting the given file in a string
	std::ifstream jsonFile{ m_SourcePath };
	std::string jsonData{};
	if (!jsonFile)
	{
		LOGERROR("Failed to find the given file: " + m_SourcePath);
		return "";
	}
	std::ostringstream ss;
	ss << jsonFile.rdbuf();
	jsonData = ss.str();

	return jsonData;
}
