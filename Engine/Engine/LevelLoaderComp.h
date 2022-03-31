#pragma once
#include "Component.h"
class LevelLoaderComp : public Component
{
public:
	LevelLoaderComp(const std::string& levelFilePath);
	~LevelLoaderComp() = default;
	LevelLoaderComp(const LevelLoaderComp& other) = delete;
	LevelLoaderComp(LevelLoaderComp&& other) = delete;
	LevelLoaderComp& operator=(const LevelLoaderComp& other) = delete;
	LevelLoaderComp& operator=(LevelLoaderComp&& other) = delete;

	void Initialize() override;

private:
	std::string m_FilePath{};

	void CreateLevel();
};

