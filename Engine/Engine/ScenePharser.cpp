#include "EnginePCH.h"
#include "ScenePharser.h"
#include "document.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransformComp.h"

void ScenePharser::CreateScenes(const std::string& filePath)
{
	rapidjson::Document sceneDocument{};
	sceneDocument.Parse(filePath.c_str());
	
    //=======FILE_FORMAT=======
	/*
	{
      "GameName": "name_of_game",
      "Scenes": [
        {
          "Scene": "1st_scene_name",
          "GameObjects": [
            {
              "Name": "1st_game_object_name",
              "Position": [0,0,0],
              "Rotation": [0,0,0],
              "Scale": [1,1,1],
              "Components": [
                {
                  "Type": "component_type",
                  "Args": ["1st_argument", 2nd_argument]
                }
              ]
            }
          ]
        }
      ]
    }
	*/

	//getting the scenes from the json file
	const rapidjson::Value& scenes{ sceneDocument["Scenes"] };
    if (!scenes.IsArray())
    {
        LOGERROR("File format was not as expected, expected an array of scenes");
        return;
    }
    if (scenes.Empty())
    {
        LOGWARNING("No scenes were found");
        return;
    }

	//looping through the scenes
	for (auto& scene : scenes.GetArray())
	{
        //adding scene to sceneManager
        if (!scene["Scene"].IsString())
        {
            LOGERROR("File format was not as expected, Scene name was not a string");
            continue;
        }

        std::string sceneName{ scene["Scene"].GetString() };
        Scene& SceneRef{ SceneManager::GetInstance().CreateScene(sceneName) };

        //getting the gameObjects of the scene from the json file
        const rapidjson::Value& gameObjects{ scene["GameObjects"] };
        if (!gameObjects.IsArray())
        {
            LOGERROR("File format was not as expected, Scene: " + sceneName + ", expected an array of game objects");
            continue;
        }
        if (gameObjects.Empty())
        {
            LOGWARNING("Scene: " + sceneName + ", no game objects were found");
            continue;
        }

        //looping through game objects
        for (auto& gameObj : gameObjects.GetArray())
        {
            //creating the game object
            if (!gameObj["Name"].IsString())
            {
                LOGERROR("File format was not as expected, Scene:" + sceneName + ", game object name was not a string");
                continue;
            }
            std::string gameObjName{ gameObj["Name"].GetString() };
            GameObject* pGameObj = new GameObject(gameObjName);

            //setting the transform of the game object
            //setting position
            pGameObj->GetTransform()->SetPos({ gameObj["Position"][0].GetFloat(),
                gameObj["Position"][1].GetFloat(),
                gameObj["Position"][2].GetFloat() });
            //setting rotation
            pGameObj->GetTransform()->SetRotation({ gameObj["Rotation"][0].GetFloat(),
                gameObj["Rotation"][1].GetFloat(),
                gameObj["Rotation"][2].GetFloat() });
            //setting scale
            pGameObj->GetTransform()->SetScale({ gameObj["Scale"][0].GetFloat(),
                gameObj["Scale"][1].GetFloat(),
                gameObj["Scale"][2].GetFloat() });

            //getting components from the game object
            const rapidjson::Value& components{ gameObj["Components"] };
            if (!components.IsArray())
            {
                LOGERROR("File format was not as expected, Scene: " + sceneName + " GameObj: " + gameObjName + 
                    ", expected an array of components");
                continue;
            }
            if (components.Empty())
            {
                LOGWARNING("Scene: " + sceneName + " GameObj: " + gameObjName + ", no components were found");
                continue;
            }

            //looping through the components
            for (auto& component : components.GetArray())
            {
                //getting the type of component
                if (!component["Type"].IsString())
                {
                    LOGERROR("File format was not as expected, Scene: " + sceneName + " GameObj: " + gameObjName +
                        ", expected a string for component type");
                    continue;
                }
                std::string compType{ component["Type"].GetString() };

                //getting the arguments for given component




            }
            
            //adding the game object to the scene
            SceneRef.Add(pGameObj);
        }
	}
}
