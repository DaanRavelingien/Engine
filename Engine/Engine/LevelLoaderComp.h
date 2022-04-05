#pragma once
#include "Component.h"
class LevelLoaderComp : public Component
{
public:
	LevelLoaderComp(const std::string& levelFilePath, const std::string& textureName);
	~LevelLoaderComp() = default;
	LevelLoaderComp(const LevelLoaderComp& other) = delete;
	LevelLoaderComp(LevelLoaderComp&& other) = delete;
	LevelLoaderComp& operator=(const LevelLoaderComp& other) = delete;
	LevelLoaderComp& operator=(LevelLoaderComp&& other) = delete;

	void Initialize() override;

private:
	std::string m_FilePath{};
	std::string m_TextureName{};

	void CreateLevel();
};

