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

	void CreateScene(const std::string& filePath);

private:
	Scene& PharseScene(const rapidjson::Value& jsonScene);
	GameObject* PharseGameObj(const rapidjson::Value& jsonGameObj);
	Component* PharseComp(const rapidjson::Value& jsonComp);

	//function to create comp from string
	Component* CreateComponent(const std::string& compType, const rapidjson::Value& args);
};

