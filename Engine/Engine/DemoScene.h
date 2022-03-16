#pragma once
#include "Scene.h"
class DemoScene : public Scene
{
public:
	DemoScene();
	~DemoScene() = default;
	DemoScene(const DemoScene& other) = delete;
	DemoScene(DemoScene&& other) = delete;
	DemoScene& operator=(const DemoScene& other) = delete;
	DemoScene& operator=(DemoScene&& other) = delete;
protected:
	void Initialize() override;

private:

};

