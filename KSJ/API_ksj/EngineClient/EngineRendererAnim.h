#pragma once
#include "EngineRenderer.h"
#include <EngineWinImage.h>
#include <EngineString.h>
#include <map>


class EngineActor;
class EngineWinImage;
class EngineRendererAnim : public EngineRenderer
{
private:
	class Animation
	{
	public:
		EngineWinImage* m_Image;
		float m_FrameTime; //이미지가 바뀔때의 시간
		float m_CurTime; //현재 애니메이션 시간
		int m_StartFrame; //시작프레임
		int m_EndFrame; //끝프레임
		int m_CurFrame; //현재프레임
		bool m_IsLoop;
		bool m_Reverse;
		bool m_EndAni;
		
	public:
		void Update();
		void Reset();

	public:
		Animation();
		~Animation();
	};

private: 
public: 
private: 
	std::map<EngineString, Animation> m_Animation; 
	Animation* m_CurAnimation;
	Animation* m_FirstAnimation; //우선 재생할 애니메이션

public:
	EngineRendererAnim();
	~EngineRendererAnim();


public: 
	EngineRendererAnim(const EngineRendererAnim& _Other) = delete;
	EngineRendererAnim(const EngineRendererAnim&& _Other) = delete;

public:
	EngineRendererAnim& operator=(const EngineRendererAnim& _Other) = delete;
	EngineRendererAnim& operator=(const EngineRendererAnim&& _Other) = delete;

private:
	Animation* FindAnimation(const EngineString& _Name);
	
public:
	void CreateAnimation(const EngineString& _AniName, const EngineString& _ImageName, int _Start, int _End, float _FrameTime = 0.1f, bool _Loop = true, bool _Reverse=false);
	void ChangeAnimation(const EngineString& _AniName);
	void FirstAnimation(const EngineString& _AniName);
	void FirstAnimationClear();
	bool IsEndAni()
	{
		return m_CurAnimation->m_EndAni;
	}

	void SetAllAnimTimer(float _Time);
public:
	void Render() override;
};

