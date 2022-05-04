#pragma once
#include <vector>
#include "EngineTimer.h"
#include "EngineDebug.h"
//�뵵 :
//���� :
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
	void CreateTimeEvent(float _Time, //�ð�
		EventTarget* _Obj, 
		void(EventTarget::* _EndFunc)(), //Ÿ�̸Ӱ� ������ ����Ǵ� �Լ�
		void(EventTarget::* _StartFunc)() = nullptr, //�����Ҷ� ����Ǵ� �Լ�
		void(EventTarget::* _StayFunc)() = nullptr)//startFunc�� ����ǰ� End�� ����Ǳ������� ��� ����Ǵ� �Լ�
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
		if (m_Events.size() <= CurEvent) //���� Events������� ���õȰ� ���ų� ũ�ٸ�
		{
			if (false == m_Loop)
			{
				return;
			}
			CurEvent = 0;//�ٽ�ó������
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

