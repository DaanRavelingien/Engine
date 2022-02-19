#pragma once

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
};

