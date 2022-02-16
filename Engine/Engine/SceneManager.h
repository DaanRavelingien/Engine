#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager();

	Scene& CreateScene(const std::string& name);
	void SetActiveScene(const std::string& sceneName);

	void Update();
	void FixedUpdate();
	void Render();
protected:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<Scene*> m_Scenes;

	Scene* m_pActiveScene{ nullptr };
};
