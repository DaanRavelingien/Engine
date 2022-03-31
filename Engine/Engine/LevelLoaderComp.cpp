#include "EnginePCH.h"
#include "LevelLoaderComp.h"
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

LevelLoaderComp::LevelLoaderComp(const std::string& levelFilePath)
	:Component{typeid(this).name()}
	,m_FilePath{levelFilePath}
{
}

void LevelLoaderComp::Initialize()
{
	CreateLevel();
}

void LevelLoaderComp::CreateLevel()
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
	std::ifstream jsonFile{ m_FilePath };
	std::string jsonData{};
	if (!jsonFile)
	{
		LOGERROR("Failed to find the given file: " + m_FilePath);
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
		LOGERROR("Failed to pharse the scene file: " + m_FilePath);
		return;
	}

	//loading the burgertime texture for the platform and ladder sprites
	int burgerTimeTextureIdx = ResourceManager::GetInstance().LoadTexture("Textures/BurgerTimeSprites.png");

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
		TextureComp* pPlatformTexture{ new TextureComp{burgerTimeTextureIdx} };
		pPlatformTexture->SetSourceRect({ 114,65,28,6 });
		pPlatformTexture->SetDestRect({ 0,16,hitboxSize.x,hitboxSize.y });
		pPlatform->AddComponent(pPlatformTexture);

		glm::vec2 hitboxPos{ platform["Position"][0].GetFloat(),platform["Position"][0].GetFloat() };
		pPlatform->GetTransform()->SetPos({ hitboxPos.x,hitboxPos.y,0 });

		//adding the ladder object as a child of the level
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
		TextureComp* pLadderTexture{ new TextureComp{burgerTimeTextureIdx} };
		pLadderTexture->SetSourceRect({ 114,65,28,6 });
		pLadderTexture->SetDestRect({ 0,16,hitboxSize.x,hitboxSize.y });
		pLadder->AddComponent(pLadderTexture);

		glm::vec2 hitboxPos{ ladder["Position"][0].GetFloat(),ladder["Position"][0].GetFloat() };
		pLadder->GetTransform()->SetPos({ hitboxPos.x,hitboxPos.y,0 });

		//adding the ladder object as a child of the level
		m_pGameObj->AddChild(pLadder);

		//also adding the game object to the scene to it can manage it
		m_pGameObj->GetScene()->AddGameObj(pLadder);
	}
}
