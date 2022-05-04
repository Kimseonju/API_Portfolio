#pragma once
#include <vector>
#include "EngineTimer.h"
#include "EngineDebug.h"
//용도 :
//설명 :
template<typename EventTarget>
class EngineTimeEventer
{
public:
	class TimeEvent
	{
	public:
		float m_Time;
		float m_MaxTime;
		EventTarget* m_Obj;
		void(EventTarget::* m_StartFunc)();
		void(EventTarget::* m_EndFunc)();
		void(EventTarget::* m_StayFunc)();
	public:
		bool Update()
		{
			if (m_Time >= m_MaxTime)
			{
				m_Time -= EngineTimer::FDeltaTime();
				if (nullptr == m_StartFunc)
				{
					return false;
				}
				(m_Obj->*m_StartFunc)();
				return false;
			}
			m_Time -= EngineTimer::FDeltaTime();

			if (0.0f <= m_Time)
			{
				if (nullptr == m_StayFunc)
				{
					return false;
				}
				(m_Obj->*m_StayFunc)();
				return false;
			}
			m_Time = m_MaxTime;

			if (nullptr == m_EndFunc)
			{
				return true;
			}
			(m_Obj->*m_EndFunc)();
			return true;

		}

	public:
		TimeEvent():m_Time(0.0f){}
		~TimeEvent() {}
	};

private:
	int CurEvent;
	std::vector<TimeEvent> m_Events;
	bool m_Loop;

public:
	void LoopOn()
	{
		m_Loop = true;
	}

public:
	void CreateTimeEvent(float _Time, //시간
		EventTarget* _Obj, 
		void(EventTarget::* _EndFunc)(), //타이머가 끝날때 실행되는 함수
		void(EventTarget::* _StartFunc)() = nullptr, //시작할때 실행되는 함수
		void(EventTarget::* _StayFunc)() = nullptr)//startFunc가 실행되고 End가 실행되기전까지 계속 실행되는 함수
	{
		m_Events.resize(m_Events.size() + 1);
		m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
		m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
		m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
		m_Events[m_Events.size() - 1].m_Obj = _Obj;
		m_Events[m_Events.size() - 1].m_Time = _Time;
		m_Events[m_Events.size() - 1].m_MaxTime = _Time;
	}

	void Update()
	{
		if (0 == m_Events.size())
		{
			EngineDebug::AssertMsg("if (0 == m_Events.size())");
		}
		if (m_Events.size() <= CurEvent) //만약 Events사이즈보다 선택된게 같거나 크다면
		{
			if (false == m_Loop)
			{
				return;
			}
			CurEvent = 0;//다시처음부터
		}

		if (true == m_Events[CurEvent].Update())
		{
			++CurEvent;
		}
	}
public:
	EngineTimeEventer() :CurEvent(), m_Loop(false)
	{
	}
	~EngineTimeEventer() {};
};

