#include "Moms_hand.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include <EngineRendererBasic.h>
void Moms_hand::FindStart()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	//플레이어와 씬이 다르면 플레이하는 상태가 아니다.
	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}
	m_RenderBody->ChangeAnimation(L"Idle");
	m_RenderHitLayer->ChangeAnimation(L"Idle");
	m_Time = 0;
}
void Moms_hand::FindStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	//플레이어와 씬이 다르면 플레이하는 상태가 아니다.
	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}

	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	Dir.Normalize();
	m_CharacterInfo->SetDir(Dir);

	if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
	{
		m_MonsterFSM.ChangeState(L"Attack");
		m_CharacterInfo->StopSpeed();
	}
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

}

void Moms_hand::MoveStart()
{
	m_Time = 0.f;
}


void Moms_hand::MoveStay()
{
	if (m_RenderBody->IsEndAni())
	{
		if (m_Time < 1.f)
		{
			float4 PivotPos = m_RenderBody->GetPivotPos();
			float4 CurPos = float4::Lerp2DMax(PivotPos, { 0,-500 }, m_Time);
			m_RenderBody->SetPivotPos(CurPos);
			m_Time += EngineTimer::FDeltaTime(GetCharacterInfo()->GetSpeed());
		}
		else
		{
			m_MonsterFSM.ChangeState(L"Find");
		}
	}
	
}

void Moms_hand::AttackStart()
{
	m_Time = 0.f;
	m_RenderBody->ChangeAnimation(L"AttackStart");
	m_RenderHitLayer->ChangeAnimation(L"AttackStart");
	m_CharacterInfo->SetAttackDelay(0.f);
}

void Moms_hand::AttackStay()
{
	//타임속도조절하기
	
	//충돌체와 이미지 위치 초기위치는 x 0 y -1000
	//-값을 0으로바꾸면서 떨어지는 느낌주기

	if (m_Time < 1.f)
	{
		m_Time += EngineTimer::FDeltaTime(GetCharacterInfo()->GetSpeed());
		float4 PivotPos = m_RenderBody->GetPivotPos();
		float4 CurPos = float4::Lerp2DMax(PivotPos, { 0,-50 }, m_Time);
		m_RenderBody->SetPivotPos(CurPos);
	}
	else
	{
		m_Collision->On();
		m_RenderBody->ChangeAnimation(L"AttackEnd");
		m_RenderHitLayer->ChangeAnimation(L"AttackEnd");
		if (m_RenderBody->IsEndAni())
		{
			m_Collision->Off();
			m_RenderBody->ChangeAnimation(L"MoveBack");
			m_RenderHitLayer->ChangeAnimation(L"MoveBack");
			m_MonsterFSM.ChangeState(L"Move");
		}

	}
	

	
}



void Moms_hand::DieStart()
{
	Enemy::DieStart();
	m_RenderHitLayer->RenderOff();
	Death();
}

void Moms_hand::DieStay()
{
	
}

void Moms_hand::DieEnd()
{
}

void Moms_hand::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Moms_hand::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Moms_hand::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}
