#pragma once
#include "Component.h"
#include "Observer.h"

class LevelManagerComp : public Component, public Observer<Component>
{
public:
	LevelManagerComp(const std::string& textureName);
	~LevelManagerComp() = default;
	LevelManagerComp(const LevelManagerComp& other) = delete;
	LevelManagerComp(LevelManagerComp&& other) = delete;
	LevelManagerComp& operator=(const LevelManagerComp& other) = delete;
	LevelManagerComp& operator=(LevelManagerComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void AddLevelFile(const std::string& levelFilePath) { m_LevelFiles.push_back(levelFilePath); };
	void ResetLvl();
	void SetFirsLvl();
	void GoNextLvl();
	void GoPrevLvl();

private:
	std::string m_TextureName{};
	int m_CurrentLevel{ 0 };

	std::vector<std::string> m_LevelFiles{};

	void Notify(Component* pComp, Event event) override;

	void CreateLevel();
	void DestroyCurrentLevel();
};

