#pragma once
#include <EngineObjectBase.h>
#include <EngineMath.h>
#include <set>
#include <vector>
//용도 :
//설명 :
class EngineActor;
class EngineCollision :public EngineObjectBase
{
private: //static
public:  //static func
private:
	COLTYPE m_Type;
	int m_Order;
	EngineActor* m_Actor;
	float4 m_PivotPos;
	float4 m_ColScale;
	Col2DData m_Data;

	std::set<EngineCollision*> m_ColSet;
public: //member

	void SetScale(const float4& _Scale)
	{
		m_Data.Size = _Scale;
	}
	float4 GetScale() const
	{
		return m_Data.Size;
	}
	void SetOrder(int _Order)
	{
		m_Order = _Order;
	}

	void SetPivotPos(const float4& _Other)
	{
		m_PivotPos = _Other;
	}
	float4& GetPivotPos()
	{
		return m_PivotPos;
	}
	int GetOrder()
	{
		return m_Order;
	}
	void SetActor(EngineActor* _Actor)
	{
		m_Actor = _Actor;
	}
	EngineActor* GetActor()
	{
		return m_Actor;
	}

	float4 GetPosition()const;
public: //constructer destructer
	EngineCollision();
	~EngineCollision();

public:
	EngineCollision(const EngineCollision& _Other) = delete;
	EngineCollision(const EngineCollision&& _Other) = delete;

public:
	EngineCollision& operator=(const EngineCollision& _Other) = delete;
	EngineCollision& operator=(const EngineCollision&& _Other) = delete;

public: //member
	void Render();
	void CollisionCheck(EngineCollision* _Other);
	void CollisionDataUpdate();


	void ReleaseUpdate();

	void DeathTask() override;
	void OffTask() override;


private:
	class EventBase
	{
	public:
		virtual void CallBack(EngineCollision* _This, EngineCollision* _Other) {}
	};
	template<typename EventType>
	class EventBaseTemplate :public EventBase
	{
	public:
		EventType* m_Obj;
		void(EventType::* m_StartFunc)(EngineCollision* _This, EngineCollision* _Other);

	public:
		void CallBack(EngineCollision* _This, EngineCollision* _Other) override
		{
			(m_Obj->*m_StartFunc)(_This, _Other);
		}

	public:
		EventBaseTemplate(EventType* _Obj, void (EventType::* _StartFunc)(EngineCollision* _This, EngineCollision* _Other))
		: m_Obj(_Obj), m_StartFunc(_StartFunc)
		{}

	};

private:
	std::vector<EventBase*> StartEvent;
	std::vector<EventBase*> StayEvent;
	std::vector<EventBase*> EndEvent;

public:
	template<typename Target>
	void AddStartEvent(Target* _Obj, void(Target::* _StartFunc)(EngineCollision* _This, EngineCollision* _Other))
	{
		StartEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
	}
	void UpdateStartEvent(EngineCollision* _This, EngineCollision* _Other)
	{
		m_ColSet.insert(_Other);
		for (int i = 0; i < StartEvent.size(); i++)
		{
			StartEvent[i]->CallBack(_This, _Other);
		}
	}
	template<typename Target>
	void AddStayEvent(Target* _Obj, void(Target::* _StartFunc)(EngineCollision* _This, EngineCollision* _Other))
	{
		StayEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
	}

	void UpdateStayEvent(EngineCollision* _This, EngineCollision* _Other)
	{
		for (size_t i = 0; i < StayEvent.size(); i++)
		{
			StayEvent[i]->CallBack(_This, _Other);
		}
	}

	template<typename Target>
	void AddEndEvent(Target* _Obj, void(Target::* _StartFunc)(EngineCollision* _This, EngineCollision* _Other))
	{
		EndEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
	}

	void UpdateEndEvent(EngineCollision* _This, EngineCollision* _Other)
	{
		for (size_t i = 0; i < EndEvent.size(); i++)
		{
			EndEvent[i]->CallBack(_This, _Other);
		}

		m_ColSet.erase(_Other);
	}
};

