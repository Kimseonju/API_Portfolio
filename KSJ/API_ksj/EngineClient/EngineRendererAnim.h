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
		float m_FrameTime; //�̹����� �ٲ��� �ð�
		float m_CurTime; //���� �ִϸ��̼� �ð�
		int m_StartFrame; //����������
		int m_EndFrame; //��������
		int m_CurFrame; //����������
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
	Animation* m_FirstAnimation; //�켱 ����� �ִϸ��̼�

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

