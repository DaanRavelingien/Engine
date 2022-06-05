#pragma once
#include <Component.h>
#include "glm\detail\type_vec3.hpp"
#include "EnemyComp.h"

class EnemyManagerComp : public Component
{
public:
	EnemyManagerComp(int enemyCount);
	~EnemyManagerComp() = default;
	EnemyManagerComp(const EnemyManagerComp& other) = delete;
	EnemyManagerComp(EnemyManagerComp&& other) = delete;
	EnemyManagerComp& operator=(const EnemyManagerComp& other) = delete;
	EnemyManagerComp& operator=(EnemyManagerComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void AddSpawnPoint(const glm::vec3& point);

	void AddEnemyTarget(GameObject* pTarget);
	void ResetEnemies();

private:
	std::vector<glm::vec3> m_SpawnPoints{};
	std::vector<GameObject*> m_Enemies{};
	std::vector<GameObject*> m_Targets{};
	int m_EnemyCount;

	float m_SpawnTime{ 5 };
	float m_SpawnTimer{ 0 };

	void AddEnemy(EnemyComp::EnemyType type);
};

