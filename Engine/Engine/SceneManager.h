#pragma once
#include "Singleton.h"
#include <string>
#include <vector>

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager();

	Scene& AddScene(Scene* pScene);
	void SetActiveScene(const std::string& sceneName);
	Scene* GetActiveScene() const { return m_pActiveScene; };

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
