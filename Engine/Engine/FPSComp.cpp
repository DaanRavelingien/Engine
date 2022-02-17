#include "EnginePCH.h"
#include "FPSComp.h"
#include "GameObject.h"
#include "TextComp.h"

void FPSComp::Initialize()
{
	m_pTextComp = m_pGameObj->GetComponent<TextComp>();

	if (m_pTextComp == nullptr)
		LOGWARNING("no text component was found");
	else
		m_pTextComp->SetText("0 FPS");
}

void FPSComp::Update()
{
	m_AverageFps += int(1 / Time::GetInstance().GetDeltaTime());
	m_SampleSize++;
	m_RefreshTime += Time::GetInstance().GetDeltaTime();

	if (m_RefreshTime >= m_RefreshRate)
	{
		std::string newText{ std::to_string(int(m_AverageFps / m_SampleSize)) + " FPS" };

		if (m_pTextComp != nullptr)
			if (m_pTextComp->GetText() != newText)
				m_pTextComp->SetText(newText);

		m_AverageFps = 0;
		m_SampleSize = 0;
		m_RefreshTime = 0.f;
	}
}
