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

	void Enable() { m_Enabled = true; };
	void Disable() { m_Enabled = false; };
	bool IsEnabled() { return m_Enabled; };

private:
	bool m_Enabled{ true };

};

