#include "EnginePCH.h"
#include "LevelManagerComp.h"
#include "document.h"
#include <fstream>
#include "GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"

//component includes
#include "TransformComp.h"
#include "TextureComp.h"
#include "TextureRenderComp.h"
#include "HitboxComp.h"
#include "HitboxManagerComp.h"
#include "IngredientManagerComp.h"

LevelManagerComp::LevelManagerComp(const std::string& textureName)
	:Component{typeid(this).name()}
	,m_TextureName{textureName}
{
}

void LevelManagerComp::Initialize()
{
	if (!m_LevelFiles.empty())
		CreateLevel();
	else
		LOGWARNING("No level was created because no level files were given");

	//adding this as an observer to the scene
	m_pGameObj->GetScene()->AddObserver(this);
}

void LevelManagerComp::Update()
{
	//if no level exists then create the one we need
	if (m_pGameObj->GetChildren().empty())
		CreateLevel();
}

void LevelManagerComp::ResetLvl()
{
	DestroyCurrentLevel();
}

void LevelManagerComp::SetFirsLvl()
{
	DestroyCurrentLevel();
	m_CurrentLevel = 0;
}

void LevelManagerComp::GoNextLvl()
{
	if (m_LevelFiles.empty())
	{
		LOGWARNING("No level was created because no level files were given");
		return;
	}

	DestroyCurrentLevel();

	m_CurrentLevel++;
	m_CurrentLevel %= (int)m_LevelFiles.size();
}

void LevelManagerComp::GoPrevLvl()
{
	if (m_LevelFiles.empty())
	{
		LOGWARNING("No level was created because no level files were given");
		return;
	}

	DestroyCurrentLevel();

	m_CurrentLevel++;
	m_CurrentLevel %= (int)m_LevelFiles.size();

	CreateLevel();
}

void LevelManagerComp::Notify(Component*, Event event)
{
	if (event == Event::BURGERS_COMPLETE)
	{
		GoNextLvl();
	}
}

void LevelManagerComp::CreateLevel()
{
	//file format example
	//===================
	//{
	//	"LevelName": "Level_1",
	//		"PlayerSpawn" : [0, 0] ,
	//		"EnemySpawns" : [
	//			[0, 0],
	//				[0, 0]
	//		],
	//		"Platforms" : [{
	//			"Size": [1, 1] ,
	//				"Position" : [0, 0]
	//		},
	//	{
	//		"Size": [1, 1] ,
	//		"Position" : [0, 0]
	//	}
	//		] ,
	//			"Ladders": [{
	//				"Size": [1, 1] ,
	//					"Position" : [0, 0]
	//			},
	//	{
	//		"Size": [1, 1] ,
	//		"Position" : [0, 0]
	//	}
	//			]
	//}

	//getting the given file in a string
	std::ifstream jsonFile{ m_LevelFiles.at(m_CurrentLevel) };
	std::string jsonData{};
	if (!jsonFile)
	{
		LOGERROR("Failed to find the given file: " + m_LevelFiles.at(m_CurrentLevel));
		return;
	}
	std::ostringstream ss;
	ss << jsonFile.rdbuf();
	jsonData = ss.str();

	//getting the string into a rapidjson document
	rapidjson::Document levelDocument{};
	levelDocument.Parse(jsonData.c_str());

	if (!levelDocument.IsObject())
	{
		LOGERROR("Failed to pharse the scene file: " + m_LevelFiles.at(m_CurrentLevel));
		return;
	}

	//creating the platforms
	int platformCount{};
	for (auto& platform : levelDocument["Platforms"].GetArray())
	{
		GameObject* pPlatform{ new GameObject{"Platform" + std::to_string(platformCount)} };
		++platformCount;

		//adding the nessecary components to the ladder object
		glm::vec2 hitboxSize{ platform["Size"][0].GetFloat(),platform["Size"][1].GetFloat() };
		pPlatform->AddComponent(new HitboxComp{ HitboxTag::Platform,hitboxSize.x,hitboxSize.y });

		pPlatform->AddComponent(new TextureRenderComp{});
		TextureComp* pPlatformTexture{ new TextureComp{m_TextureName} };
		pPlatformTexture->SetSourceRect({ 0,165,hitboxSize.x,3 });
		pPlatformTexture->SetDestRect({ 0,16,hitboxSize.x,3 });
		pPlatform->AddComponent(pPlatformTexture);

		glm::vec2 hitboxPos{ platform["Position"][0].GetFloat() * m_pGameObj->GetTransform()->GetScale().x,
			platform["Position"][1].GetFloat() * m_pGameObj->GetTransform()->GetScale().y };
		pPlatform->GetTransform()->SetPos({ hitboxPos.x,hitboxPos.y,-3 });

		//adding the platform object as a child of the level
		m_pGameObj->AddChild(pPlatform);

		//also adding the game object to the scene to it can manage it
		m_pGameObj->GetScene()->AddGameObj(pPlatform);
	}

	//creating the ladders
	int ladderCount{};
	for (auto& ladder : levelDocument["Ladders"].GetArray())
	{
		GameObject* pLadder{ new GameObject{"Ladder" + std::to_string(ladderCount)} };
		++ladderCount;

		//adding the nessecary components to the ladder object
		glm::vec2 hitboxSize{ ladder["Size"][0].GetFloat(),ladder["Size"][1].GetFloat() };
		pLadder->AddComponent(new HitboxComp{ HitboxTag::Ladder,hitboxSize.x,hitboxSize.y });

		pLadder->AddComponent(new TextureRenderComp{});
		TextureComp* pLadderTexture{ new TextureComp{m_TextureName} };
		pLadderTexture->SetSourceRect({ 195,1,10,hitboxSize.y });
		pLadderTexture->SetDestRect({ ((int)hitboxSize.x - 10) / 2,16,10,hitboxSize.y });
		pLadder->AddComponent(pLadderTexture);

		glm::vec2 hitboxPos{ ladder["Position"][0].GetFloat() * m_pGameObj->GetTransform()->GetScale().x,
			ladder["Position"][1].GetFloat() * m_pGameObj->GetTransform()->GetScale().y };
		pLadder->GetTransform()->SetPos({ hitboxPos.x,hitboxPos.y,-4 });

		//adding the ladder object as a child of the level
		m_pGameObj->AddChild(pLadder);

		//also adding the game object to the scene to it can manage it
		m_pGameObj->GetScene()->AddGameObj(pLadder);
	}

	//creating burger trays
	int trayCount{ 0 };
	for (auto& tray : levelDocument["BurgerTrays"].GetArray())
	{
		GameObject* pTray{ new GameObject{"Tray" + std::to_string(trayCount)} };
		++trayCount;

		//adding the nessecary components
		pTray->AddComponent(new HitboxComp{ HitboxTag::Tray, 38,5 });
		pTray->AddComponent(new TextureRenderComp{});
		TextureComp* pTrayTexture{ new TextureComp{m_TextureName} };
		pTrayTexture->SetSourceRect({ 101,87,38,5 });
		pTrayTexture->SetDestRect({ 0,0,38,5 });
		pTray->AddComponent(pTrayTexture);

		glm::vec2 pos{ tray["Position"][0].GetFloat() * m_pGameObj->GetTransform()->GetScale().x,
			tray["Position"][1].GetFloat() * m_pGameObj->GetTransform()->GetScale().y };
		pTray->GetTransform()->SetPos({ pos.x,pos.y,0 });

		//adding the ladder object as a child of the level
		m_pGameObj->AddChild(pTray);

		//also adding the game object to the scene to it can manage it
		m_pGameObj->GetScene()->AddGameObj(pTray);
	}

	//for the ingredients we will store them seperatly under an ingredient obj
	GameObject* pIngredients{ new GameObject{"Ingredients"} };
	IngredientManagerComp* pIngredientManager{ new IngredientManagerComp{} };
	pIngredients->AddComponent(pIngredientManager);
	m_pGameObj->AddChild(pIngredients);

	//adding the ingredients to the scene
	for (auto& ingredient : levelDocument["BurgerIngredients"].GetArray())
	{
		glm::vec2 position{ ingredient["Position"][0].GetFloat(), ingredient["Position"][1].GetFloat() };

		pIngredientManager->CreateIngredient(ingredient["Type"].GetString(), position);
	}

	//adding the ingredients to the scene so they are managed and updated
	m_pGameObj->GetScene()->AddGameObj(pIngredients);
}

void LevelManagerComp::DestroyCurrentLevel()
{
	//destroying the chilren of the current level
	for (GameObject* pChild : m_pGameObj->GetChildren())
	{
		pChild->Destroy();
	}
}

