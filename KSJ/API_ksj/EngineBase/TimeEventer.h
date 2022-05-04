#pragma once
#pragma once
#include <vector>
#include "EngineTimer.h"
#include "EngineDebug.h"

template<typename EventTarget>
class TimeEventer
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
				m_Time -= GameEngineTimer::FDeltaTime();
				if (nullptr == m_StartFunc)
				{
					return false;
				}
				(m_Obj->*m_StartFunc)();
				return false;
			}

			m_Time -= GameEngineTimer::FDeltaTime();

			if (0.0 <= m_Time)
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
		TimeEvent() : m_Time(0.0f)
		{

		}
		~TimeEvent()
		{

		}
	};

private:
	int CurEvent;
	std::vector<TimeEvent> m_Events;
	bool  m_Loop; 

public:
	void LoopOn()
	{
		m_Loop = true;
	}


public:
	void CreateTimeEvent(float _Time, EventTarget* _Obj,
		void(EventTarget::* _EndFunc)(), 
		void(EventTarget::* _StartFunc)() = nullptr,
		void(EventTarget::* _StayFunc)() = nullptr  
	)
	{
		m_Events.resize(m_Events.size() + 1);
		m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
		m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
		m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
		m_Events[m_Events.size() - 1].m_Time = _Time;
		m_Events[m_Events.size() - 1].m_MaxTime = _Time;
		m_Events[m_Events.size() - 1].m_Obj = _Obj;
	}

	void Update()
	{
		if (0 == m_Events.size())
		{
			GameEngineDebug::AssertMsg("if (0 == m_Events.size())");
		}

		if (m_Events.size() <= CurEvent)
		{
			if (false == m_Loop)
			{
				return;
			}
			CurEvent = 0;
		}

		if (true == m_Events[CurEvent].Update())
		{
			++CurEvent;
		}
	}

public:
	TimeEventer() : CurEvent(0), m_Loop(false)
	{

	}
	~TimeEventer()
	{

	}

};

