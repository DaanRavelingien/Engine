#pragma once
#include "Component.h"

class TextComp;

class FPSComp final : public Component
{
public:
	explicit FPSComp(float refreshRate = 0.5f);
	~FPSComp() = default;
	FPSComp(const FPSComp& other) = delete;
	FPSComp(FPSComp&& other) = delete;
	FPSComp& operator=(const FPSComp& other) = delete;
	FPSComp& operator=(FPSComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	//static function to create comp from arguments
	static Component* CreateComp(const rapidjson::Value& args);
private:
	float m_AverageFps{};
	int m_SampleSize{};
	float m_RefreshTime{};
	float m_RefreshRate;

	TextComp* m_pTextComp{ nullptr };
};

