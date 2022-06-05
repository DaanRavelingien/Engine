#pragma once
#include <Singleton.h>
#include <string>

class BurgerTimeData : public Singleton<BurgerTimeData>
{
public:
	~BurgerTimeData() = default;

	void SetSourcePath(const std::string& path) { m_SourcePath = path; };

	enum class GameMode
	{
		Single, CoOp, Vs
	};

	int GetHeighScore(GameMode gameMode);
	int GetScore(GameMode gameMode);

	void SetHeighScore(GameMode gameMode, int score);
	void SetScore(GameMode gameMode, int score);
	
	int GetGameVolume();

protected:
	friend class Singleton<BurgerTimeData>;
	BurgerTimeData() = default;

private:
	std::string m_SourcePath{};

	std::string GetDataSring();

};

