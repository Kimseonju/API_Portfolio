#pragma once
#include "EngineMath.h"
//용도 :
//설명 :
class EngineObjectBase
{
private:

	bool m_IsOn;
	bool m_IsDeath;


	bool m_IsOnTask;
	bool m_IsOffTask;

	EngineObjectBase* m_Parent;

public:

	EngineObjectBase* GetParentBase()
	{
		return m_Parent;
	}

	void SetParentBase(EngineObjectBase* _Parent)
	{
		m_Parent = _Parent;
	}

public:
	void CallOffTask() 
	{
		if (true == m_IsOffTask)
		{
			OffTask();
			m_IsOffTask = false;
		}
	}

	bool IsOffTask() 
	{
		return m_IsOffTask;
	}



	void CallOnTask()
	{
		if (true == m_IsOnTask)
		{
			OnTask();
			m_IsOnTask = false;
		}
	}


public:
	bool IsOn()
	{
		if (nullptr == m_Parent)
		{
			return m_IsOn && (false == m_IsDeath);
		}

		return (m_IsOn && (false == m_IsDeath)) && m_Parent->IsOn();
	}

	void On()
	{
		if (false == m_IsOn)
		{
			m_IsOnTask = true;
			// OnTask();
		}
		m_IsOn = true;
	}

	void Off()
	{
		if (true == m_IsOn)
		{
			m_IsOffTask = true;
			// OffTask();
		}
		m_IsOn = false;
	}

	bool IsDeath()
	{
		if (nullptr == m_Parent)
		{
			return m_IsDeath;
		}
		return m_IsDeath || m_Parent->IsDeath();
	}

	void Death()
	{
		m_IsDeath = true;
	}

public:

	virtual void OnTask() { } //켜질때실행
	virtual void OffTask() { } //꺼질때실행
	virtual void DeathTask() { } //Death 때 실행

public:
	virtual float4 GetPosition() { return float4::ZERO; }
	virtual void SetPosition(const float4& _Other){}

	virtual void MovePosition(const float4& _Other){}
public: //constructer destructer
	EngineObjectBase();
	virtual ~EngineObjectBase();

public: 
	EngineObjectBase(const EngineObjectBase& _Other) = delete;
	EngineObjectBase(const EngineObjectBase&& _Other) = delete;

public:
	EngineObjectBase& operator=(const EngineObjectBase& _Other) = delete;
	EngineObjectBase& operator=(const EngineObjectBase&& _Other) = delete;

public: //member
};

