#include "EngineRendererAnim.h"
#include "EngineWindowResMgr.h"
#include "EngineWinImage.h"
#include <EngineDebug.h>
#include <EngineWindow.h>

EngineRendererAnim::Animation::Animation() :
	m_Image(nullptr),
	m_FrameTime(0.1f),
	m_CurTime(0.0f),
	m_StartFrame(-1),
	m_EndFrame(-1),
	m_CurFrame(-1),
	m_IsLoop(true),
	m_Reverse(false),
	m_EndAni(false)
{
}

EngineRendererAnim::Animation::~Animation()
{
}

void EngineRendererAnim::Animation::Update()
{

	m_CurTime -= EngineTimer::FDeltaTime();
	if (0 >= m_CurTime)
	{
		m_CurTime = m_FrameTime;
		if (!m_Reverse)
		{
			++m_CurFrame;
			if (m_CurFrame > m_EndFrame)
			{
				if (true == m_IsLoop)
				{
					m_CurFrame = m_StartFrame;
				}
				else
				{
					--m_CurFrame;
					m_EndAni = true;
				}
			}
		}
		else
		{
			--m_CurFrame;
			if (m_CurFrame < m_StartFrame)
			{
				if (true == m_IsLoop)
				{
					m_CurFrame = m_EndFrame;
				}
				else
				{
					++m_CurFrame;
					m_EndAni = true;
				}
			}
		}
	}
}

void EngineRendererAnim::Animation::Reset()
{
	m_CurTime = m_FrameTime;
	m_CurFrame = m_StartFrame;
	m_EndAni = false;
}


EngineRendererAnim::EngineRendererAnim():
	m_CurAnimation(nullptr),
	m_FirstAnimation(nullptr)
{
	m_RenderingType = RENDERINGMODE::TRANS;
}

EngineRendererAnim::~EngineRendererAnim()
{
}

EngineRendererAnim::Animation* EngineRendererAnim::FindAnimation(const EngineString& _Name)
{
	if (m_Animation.end() == m_Animation.find(_Name))
	{
		return nullptr;
	}
	return &m_Animation[_Name];
}

void EngineRendererAnim::CreateAnimation(const EngineString& _AniName, const EngineString& _ImageName, int _Start, int _End, float _FrameTime, bool _Loop, bool _Reverse)
{
	EngineWinImage* FindImage = EngineWindowResMgr::Inst().FindImage(_ImageName);
	if (nullptr == FindImage)
	{
		EngineDebug::AssertMsg("if (nullptr == FindImage)");
	}
	if (0 >= FindImage->GetCutSize())
	{
		EngineDebug::AssertMsg("if (0 >= FindImage->GetCurSize())");
	}

	if (0 > _Start || 0 > _End || _Start >= FindImage->GetCutSize() || _End >= FindImage->GetCutSize() || _End < _Start)
	{
		EngineDebug::AssertMsg("_Start _End Error");
	}

	if (nullptr != FindAnimation(_AniName))
	{
		EngineDebug::AssertMsg("if (nullptr != FindAnimation(_AniName))");
	}


	Animation& NewAni = m_Animation[_AniName];
	NewAni.m_Image = FindImage;
	NewAni.m_EndFrame = _End;
	NewAni.m_StartFrame = _Start;
	NewAni.m_FrameTime = _FrameTime;
	NewAni.m_IsLoop = _Loop;
	NewAni.m_Reverse = _Reverse;
	NewAni.Reset();
}

void EngineRendererAnim::ChangeAnimation(const EngineString& _AniName)
{
	EngineRendererAnim::Animation* FindAnim = FindAnimation(_AniName);
	if (nullptr == FindAnim)
	{
		EngineDebug::AssertMsg("if (nullptr == FindAnimation)");
	}
	;
	if (m_CurAnimation == FindAnim)
		return;
	m_CurAnimation = FindAnim;
	m_CurAnimation->Reset();

	if (m_CurAnimation->m_Reverse)
	{
		m_CurAnimation->m_CurFrame = m_CurAnimation->m_EndFrame;
	}
}

void EngineRendererAnim::FirstAnimation(const EngineString& _AniName)
{
	EngineRendererAnim::Animation* FindAnim = FindAnimation(_AniName);
	if (nullptr == FindAnim)
	{
		EngineDebug::AssertMsg("if (nullptr == FindAnimation)");
	}
	;
	if (m_FirstAnimation == FindAnim)
		return;
	m_FirstAnimation = FindAnim;
	m_FirstAnimation->Reset();
	if (m_FirstAnimation->m_Reverse)
	{
		m_FirstAnimation->m_CurFrame = m_FirstAnimation->m_EndFrame;
	}
}

void EngineRendererAnim::SetAllAnimTimer(float _Time)
{
	std::map<EngineString, Animation>::iterator iter = m_Animation.begin();
	std::map<EngineString, Animation>::iterator iterEnd = m_Animation.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter).second.m_FrameTime = _Time;
	}
}


void EngineRendererAnim::FirstAnimationClear()
{
	m_FirstAnimation = nullptr;
}

void EngineRendererAnim::Render()
{
	Animation* PlayAnimation;
	if (nullptr == m_CurAnimation)
	{
		EngineDebug::AssertMsg("if (nullptr == m_CurAnimation)");
	}

	if (nullptr != m_FirstAnimation)
	{
		PlayAnimation = m_FirstAnimation;
	}
	else
	{
		PlayAnimation = m_CurAnimation;
	}
	PlayAnimation->Update();
	
	const CutData& _Data = PlayAnimation->m_Image->GetCutData(PlayAnimation->m_CurFrame);
	m_CutPos = _Data.m_Pos;
	m_CutSize = _Data.m_Size;
	if (m_RenderOn)
	{
		RenderImage(m_CurAnimation->m_Image);
	}
	
}
