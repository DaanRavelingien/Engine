#pragma once
#include "document.h"

class Scene;
class GameObject;
class Component;

class ScenePharser
{
public:
	ScenePharser() = default;
	~ScenePharser() = default;
	ScenePharser(const ScenePharser& other) = delete;
	ScenePharser(ScenePharser&& other) = delete;
	ScenePharser& operator=(const ScenePharser& other) = delete;
	ScenePharser& operator=(ScenePharser&& other) = delete;

	void CreateScenes(const std::string& filePath);

private:
	Scene& PharseScene(const rapidjson::Value& jsonScene);
	GameObject* PharseGameObj(const rapidjson::Value& jsonGameObj);
	Component* PharseComp(const rapidjson::Value& jsonComp);

	//function to create comp from string
	Component* CreateComponent(const std::string& compType, const rapidjson::Value& args);

	//functions to create components
	Component* CreateTransformComp(const rapidjson::Value& args);
	Component* CreateRenderComp(const rapidjson::Value& args);
	Component* CreateFPSComp(const rapidjson::Value& args);
	Component* CreateTextComp(const rapidjson::Value& args);
	Component* CreateTextrueComp(const rapidjson::Value& args);
};

