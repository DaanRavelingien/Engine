#include "EnginePCH.h"
#include "SpriteComp.h"
#include "GameObject.h"
#include "TextureComp.h"

SpriteComp::SpriteComp(int frames,const glm::vec2& framePxlSize, const glm::vec2& startFramePos, float frameTime)
	:Component(typeid(this).name())
	, m_FrameCount{frames}
	, m_FramePxlSize{ framePxlSize }
	,m_StartFramePos{startFramePos}
	, m_FrameTime{frameTime}
{
}

void SpriteComp::Initialize()
{
	m_pTextureComp = m_pGameObj->GetComponent<TextureComp>();

	if (m_pTextureComp == nullptr)
	{
		LOGWARNING("no texture component was found");
		return;
	}

	//setting the destination rectangle so that its the same size as our frame size
	m_pTextureComp->SetDestRect({ 0, 0, m_FramePxlSize.x, m_FramePxlSize.y });

}

void SpriteComp::Update()
{
	//updating the frame counter
	int oldFrameNr{ m_CurrentFrame };
	m_ElapsedFrameTime += float(Time::GetInstance().GetDeltaTime());
	if (m_ElapsedFrameTime >= m_FrameTime)
	{
		m_ElapsedFrameTime = 0;
		m_CurrentFrame++;

		m_CurrentFrame %= m_FrameCount;
	}

	//only update if the frame nr has changed
	if (oldFrameNr != m_CurrentFrame)
	{
		//setting the correct srource rectangele for the texture
		glm::vec4 srcRect{};
		srcRect.x = m_StartFramePos.x + m_FramePxlSize.x * m_CurrentFrame;
		srcRect.y = m_StartFramePos.y;
		srcRect.z = float(m_FramePxlSize.x);
		srcRect.w = float(m_FramePxlSize.y);

		m_pTextureComp->SetSourceRect(srcRect);
	}
}
