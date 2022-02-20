#include "EnginePCH.h"
#include "ScenePharser.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include <fstream>

//including components
#include "TransformComp.h"
#include "Render2DComp.h"
#include "TextureComp.h"
#include "TextComp.h"
#include "FPSComp.h"

void ScenePharser::CreateScenes(const std::string& filePath)
{
    //getting the given file in a string
    std::ifstream jsonFile{ filePath };
    std::string jsonData{};
    if (!jsonFile)
    {
        LOGERROR("Failed to find the given file: " + filePath);
        return;
    }
    std::ostringstream ss;
    ss << jsonFile.rdbuf();
    jsonData = ss.str();

    //getting the string into a rapidjson document
	rapidjson::Document sceneDocument{};
    sceneDocument.Parse(jsonData.c_str());

    if (!sceneDocument.IsObject())
    {
        LOGERROR("Failed to pharse the scene file: " + filePath);
        return;
    }

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
    if (!sceneDocument["Scenes"].IsArray())
    {
        LOGERROR("File format was not as expected, expected an array of scenes");
        return;
    }
    if (sceneDocument["Scenes"].Empty())
    {
        LOGWARNING("No scenes were found");
        return;
    }
    const rapidjson::Value& scenes{ sceneDocument["Scenes"].GetArray() };

	//looping through the scenes
	for (auto& scene : scenes.GetArray())
	{
        Scene& sceneRef{ PharseScene(scene) };

        //getting the gameObjects of the scene from the json file
        if (!scene["GameObjects"].IsArray())
        {
            LOGERROR("File format was not as expected, Scene: " + sceneRef.GetName() + ", expected an array of game objects");
            continue;
        }
        if (scene["GameObjects"].Empty())
        {
            LOGWARNING("Scene: " + sceneRef.GetName() + ", no game objects were found");
            continue;
        }

        //looping through game objects
        for (auto& gameObj : scene["GameObjects"].GetArray())
        {
            GameObject* pGameObj{ PharseGameObj(gameObj) };

            //getting components from the game object
            if (!gameObj["Components"].IsArray())
            {
                LOGERROR("File format was not as expected, Scene: " + sceneRef.GetName() + " GameObj: " + pGameObj->GetName() +
                    ", expected an array of components");
                continue;
            }
            if (gameObj["Components"].Empty())
            {
                LOGWARNING("Scene: " + sceneRef.GetName() + " GameObj: " + pGameObj->GetName() + ", no components were found");
                continue;
            }

            //looping through the components
            for (auto& component : gameObj["Components"].GetArray())
            {
                Component* pComponent{ PharseComp(component) };
                pGameObj->AddComponent(pComponent);
            }
            
            //adding the game object to the scene
            sceneRef.Add(pGameObj);
        }
	}
}

Scene& ScenePharser::PharseScene(const rapidjson::Value& jsonScene)
{
    //adding scene to sceneManager
    if (!jsonScene["Scene"].IsString())
        LOGERROR("File format was not as expected, Scene name was not a string");

    std::string sceneName{ jsonScene["Scene"].GetString() };
    Scene& SceneRef{ SceneManager::GetInstance().CreateScene(sceneName) };

    return SceneRef;
}

GameObject* ScenePharser::PharseGameObj(const rapidjson::Value& jsonGameObj)
{
    //creating the game object
    if (!jsonGameObj["Name"].IsString())
        LOGERROR("File format was not as expected, game object name was not a string");

    std::string gameObjName{ jsonGameObj["Name"].GetString() };
    GameObject* pGameObj = new GameObject(gameObjName);

    //setting the transform of the game object
    //setting position
    pGameObj->GetTransform()->SetPos({ jsonGameObj["Position"][0].GetFloat(),
        jsonGameObj["Position"][1].GetFloat(),
        jsonGameObj["Position"][2].GetFloat() });
    //setting rotation
    pGameObj->GetTransform()->SetRotation({ jsonGameObj["Rotation"][0].GetFloat(),
        jsonGameObj["Rotation"][1].GetFloat(),
        jsonGameObj["Rotation"][2].GetFloat() });
    //setting scale
    pGameObj->GetTransform()->SetScale({ jsonGameObj["Scale"][0].GetFloat(),
        jsonGameObj["Scale"][1].GetFloat(),
        jsonGameObj["Scale"][2].GetFloat() });

    return pGameObj;
}

Component* ScenePharser::PharseComp(const rapidjson::Value& jsonComp)
{
    //getting the type of component
    if (!jsonComp["Type"].IsString())
        LOGERROR("File format was not as expected, expected a string for component type");

    std::string compType{ jsonComp["Type"].GetString() };

    //getting the arguments for given component
    const rapidjson::Value& arguments{ jsonComp["Args"] };
    if (!arguments.IsArray())
        LOGERROR("File format was not as expected, expected an array of arguments");
    
    //create component
    Component* pComponent{ CreateComponent(compType,arguments) };

    return pComponent;
}

Component* ScenePharser::CreateComponent(const std::string& compType, const rapidjson::Value& args)
{
    Component* pComponent{ nullptr };
    if (compType.compare("RENDERCOMP") == 0)
        pComponent = CreateRenderComp(args);
    else if (compType.compare("TEXTURECOMP") == 0)
        pComponent = CreateTextrueComp(args);
    else if (compType.compare("TEXTCOMP") == 0)
        pComponent = CreateTextComp(args);
    else if (compType.compare("TRANSFORMCOMP") == 0)
        pComponent = CreateTransformComp(args);
    else if (compType.compare("FPSCOMP") == 0)
        pComponent = CreateFPSComp(args);

    return pComponent;
}

Component* ScenePharser::CreateTransformComp(const rapidjson::Value&)
{
    TransformComp* pComp{ new TransformComp{} };
    return pComp;
}

Component* ScenePharser::CreateRenderComp(const rapidjson::Value&)
{
    Render2DComp* pRenderComp{ new Render2DComp{} };
    return pRenderComp;
}

Component* ScenePharser::CreateFPSComp(const rapidjson::Value& args)
{
    FPSComp* pFPSComp{ nullptr };
    if (args.Empty())
        pFPSComp = new FPSComp{};
    else
    {
        if (!args[0].IsFloat())
            LOGERROR("Expected different type of argument for component of type: FPSCOMP");
        else
            pFPSComp = new FPSComp{ args[0].GetFloat() };
    }

    return pFPSComp;
}

Component* ScenePharser::CreateTextComp(const rapidjson::Value& args)
{
    TextComp* pTextComp{ nullptr };
    
    if (args.Empty())
        LOGERROR("Expected arguments for component of type: TEXTCOMP");
    else
    {
        if (!args[0].IsString() || !args[1].IsString() || !args[2].IsInt() || !args[3].IsArray())
            LOGERROR("Expected different type of argument for component of type : TEXTCOMP");
        else
        {
            pTextComp = new TextComp{ args[0].GetString(), args[1].GetString(), unsigned int(args[2].GetInt())
                , {args[3][0].GetFloat(),args[3][1].GetFloat(),args[3][2].GetFloat()} };
        }
    }

    return pTextComp;
}

Component* ScenePharser::CreateTextrueComp(const rapidjson::Value& args)
{
    TextureComp* pTextureComp{ nullptr };

    if(args.Empty())
        LOGERROR("Expected arguments for component of type: TEXTURECOMP");
    else
    {
        if (!args[0].IsString())
            LOGERROR("Expected different type of argument for component of type : TEXTURECOMP");
        else
            pTextureComp = new TextureComp{ args[0].GetString() };
    }

    return pTextureComp;
}
