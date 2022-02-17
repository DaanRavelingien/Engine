#pragma once
#include "Component.h"

class TextComp;

class FPSComp final : public Component
{
public:
	explicit FPSComp() = default;
	~FPSComp() = default;
	FPSComp(const FPSComp& other) = delete;
	FPSComp(FPSComp&& other) = delete;
	FPSComp& operator=(const FPSComp& other) = delete;
	FPSComp& operator=(FPSComp&& other) = delete;

	void Initialize() override;
	void Update() override;

private:
	float m_AverageFps{};
	int m_SampleSize{};
	float m_RefreshTime{};
	float m_RefreshRate{0.2f};

	TextComp* m_pTextComp{ nullptr };
};

