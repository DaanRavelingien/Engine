#include "EnginePCH.h"
#include "SpriteComp.h"
#include "GameObject.h"
#include "TextureComp.h"

//static function
Component* SpriteComp::CreateComp(const rapidjson::Value& args)
{
	SpriteComp* pSpriteComp{ nullptr };

	if (args.Empty())
		LOGERROR("Expected arguments for component of type: SPRITECOMP");
	else
	{
		if (!args[0].IsInt() || !args[1].IsArray() || !args[2].IsArray() || !args[3].IsFloat()
			|| !args[1][0].IsInt() || !args[1][1].IsInt() || !args[2][0].IsInt() || !args[2][1].IsInt())
			LOGERROR("Expected different type of argument for component of type : TEXTURECOMP");
		else
		{
			pSpriteComp = new SpriteComp{
				args[0].GetInt(),
				glm::vec2{args[1][0].GetInt(),args[1][1].GetInt()},
				glm::vec2{args[2][0].GetInt(),args[2][1].GetInt()},
				args[3].GetFloat()
			};
		}
	}

	return pSpriteComp;
}

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
