#pragma once
#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager();

	Scene& AddScene(Scene* pScene);
	void SetActiveScene(const std::string& sceneName);

	void Initialize();
	void Update();
	void FixedUpdate();
	void Render();
#ifdef _DEBUG
	void RenderGui();
#endif //_DEBUG

protected:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<Scene*> m_Scenes;

	Scene* m_pActiveScene{ nullptr };
};
