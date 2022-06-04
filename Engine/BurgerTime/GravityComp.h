#pragma once
#include "Component.h"

class GravityComp : public Component
{
public:
	GravityComp();
	~GravityComp() = default;
	GravityComp(const GravityComp& other) = delete;
	GravityComp(GravityComp&& other) = delete;
	GravityComp& operator=(const GravityComp& other) = delete;
	GravityComp& operator=(GravityComp&& other) = delete;

	void Update() override;
};

