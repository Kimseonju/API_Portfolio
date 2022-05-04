#include "CCharacterInfo.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
// Static Var
// Static Func

// member Var
CCharacterInfo::CCharacterInfo()
	:m_Speed(100.f)
	, m_DamageSpeed(float4::ZERO)
	, m_AttackDelayMax(0.4f)
	, m_AttackDelay(0.5f)
	, m_ShotSpeed(1.f)
	, m_Att(10)
	, m_ShotRange(200)
	, m_HP(10)
	, m_HPMax(10)
	, m_MaxSpeed(200.f)
	, m_ObjectMaxSpeed(0.f)
	, m_Coin(0)
	, m_Bomb(0)
	, m_Key(0)
	, m_Dir(float4::ZERO)
	,m_Timer(0.f)
	, m_AccelSpeed(float4::ZERO)
	, m_SaveAccel(float4::ZERO)
{
}

CCharacterInfo::~CCharacterInfo()
{

}
void CCharacterInfo::Update()
{
	//가속도 
	//아이작 가속도 다 가속도...
	m_Accel = m_Dir * m_Speed;

	m_AccelSpeed += m_Accel + m_DamageSpeed;
	float4 Reverse;
	Reverse.x = -m_AccelSpeed.x;
	Reverse.y = -m_AccelSpeed.y;
	Reverse.Normalize();

	float4 DamageReverse;
	DamageReverse.x = -m_DamageSpeed.x;
	DamageReverse.y = -m_DamageSpeed.y;
	m_DamageSpeed += DamageReverse * 0.05f;
	float fSpeed = m_AccelSpeed.Len();
	if (fSpeed < 5.f)
	{
		m_AccelSpeed = float4::ZERO;
	}
	else
	{
		float len = m_AccelSpeed.Len();
		m_AccelSpeed += Reverse * len*0.1f;
	}

	if (m_MaxSpeed < m_AccelSpeed.Len())
	{
		
		if(m_ObjectMaxSpeed==0.f)
		{
			m_AccelSpeed.Normalize();
			m_AccelSpeed = m_AccelSpeed * m_MaxSpeed;
		}
	}
}