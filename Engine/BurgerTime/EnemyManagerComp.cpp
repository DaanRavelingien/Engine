#include "EnginePCH.h"
#include "EnemyManagerComp.h"
#include "GameObject.h"
#include "Scene.h"

//component includes
#include "TextureRenderComp.h"
#include "TextureComp.h"
#include "HitboxComp.h"
#include "EntityMoveComp.h"
#include "GravityComp.h"
#include "HotDogBehaviourComp.h"
#include "TransformComp.h"

EnemyManagerComp::EnemyManagerComp(int enemyCount)
	:Component{ typeid(this).name() }
	,m_EnemyCount{enemyCount}
{
}

void EnemyManagerComp::Initialize()
{}

void EnemyManagerComp::Update()
{
	//create the enemies with a delay to ramp up the difficulty
	m_SpawnTimer += GameTime::GetInstance().GetDeltaTime();
	if (m_SpawnTime < m_SpawnTimer)
	{
		if (m_EnemyCount > 1 && (int)m_Enemies.size() == m_EnemyCount - 1)
			AddEnemy(EnemyComp::EnemyType::MrEgg);
		else if ((int)m_Enemies.size() % 2 == 1)
			AddEnemy(EnemyComp::EnemyType::MrPickle);
		else
			AddEnemy(EnemyComp::EnemyType::MrHotDog);

		m_SpawnTimer = 0;
	}
}

void EnemyManagerComp::AddSpawnPoint(const glm::vec3& point)
{
	m_SpawnPoints.push_back(point);
}

void EnemyManagerComp::AddEnemyTarget(GameObject* pTarget)
{
	for (GameObject* pEnemy : m_Enemies)
	{
		pEnemy->GetComponent<HotDogBehaviourComp>()->AddTarget(pTarget);
	}

	m_Targets.push_back(pTarget);
}

void EnemyManagerComp::ResetEnemies()
{
	for (GameObject* pEnemy : m_Enemies)
	{
		pEnemy->GetComponent<EntityMoveComp>()->Respawn();
		pEnemy->GetComponent<HotDogBehaviourComp>()->Reset();
		pEnemy->Disable();
	}

	m_SpawnTimer = 0;
}

void EnemyManagerComp::AddEnemy(EnemyComp::EnemyType type)
{
	if (m_SpawnPoints.empty())
	{
		LOGWARNING("Could not spawn enemy because there are no spawnpoints");
		return;
	}

	//first we will look if we have any disabled enemies in our vector otherwise we make a new one
	auto it = std::find_if(m_Enemies.begin(), m_Enemies.end(), [type](GameObject* pEnemy)
		{
			if (pEnemy->GetComponent<EnemyComp>()->GetEnemyType() == type
				&& pEnemy->IsDisabled())
				return true;
			return false;

		});

	if (it != m_Enemies.end())
	{
		//enabeling the enemy again
		(*it)->Enable();
		(*it)->GetComponent<EntityMoveComp>()->Respawn();
		(*it)->GetComponent<HotDogBehaviourComp>()->Reset();
	}
	//check if we can add any more enemies
	else if ((int)m_Enemies.size() < m_EnemyCount)
	{
		Component* pBehaviour{};
		glm::vec4 sourceRect{};

		switch (type)
		{
		case EnemyComp::EnemyType::MrHotDog:
			pBehaviour = new HotDogBehaviourComp{};
			sourceRect = glm::vec4{ 0,32,16,16 };
			break;
		case EnemyComp::EnemyType::MrPickle:
			pBehaviour = new HotDogBehaviourComp{};
			sourceRect = glm::vec4{ 0,64,16,16 };
			break;
		case EnemyComp::EnemyType::MrEgg:
			pBehaviour = new HotDogBehaviourComp{};
			sourceRect = glm::vec4{ 0,96,16,16 };
			break;
		default:
			break;
		}

		GameObject* pEnemy{ new GameObject{ "Enemy" + std::to_string(m_Enemies.size())} };
		pEnemy->AddComponent(new TextureRenderComp{});

		TextureComp* pEnemyTexture{ new TextureComp{"BurgerTimeTexture"} };
		pEnemyTexture->SetSourceRect(sourceRect);
		pEnemyTexture->SetDestRect({ 0,0,16,16 });
		pEnemy->AddComponent(pEnemyTexture);
		pEnemy->AddComponent(new HitboxComp{ HitboxTag::Enemy, 16,16,
			HitboxManagerComp::CollisionGroup::CollisionGroup1 });

		//setting the spawn point of this enemy
		glm::vec3 spawnPoint{ m_SpawnPoints.at(int(m_Enemies.size()) % int(m_SpawnPoints.size())) };
		pEnemy->AddComponent(new EntityMoveComp{ spawnPoint });

		pEnemy->AddComponent(new EnemyComp{ type });
		pEnemy->AddComponent(new GravityComp{});
		pEnemy->AddComponent(pBehaviour);

		for (GameObject* pTarget : m_Targets)
		{
			pEnemy->GetComponent<HotDogBehaviourComp>()->AddTarget(pTarget);
		}

		pEnemy->GetTransform()->SetScale({ 3,3,3 });

		m_Enemies.push_back(pEnemy);

		//adding the enemies to the scene
		GetGameObj()->GetScene()->AddGameObj(pEnemy);
	}
}
