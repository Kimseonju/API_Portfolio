#include "Turret.h"
#include "LogicValue.h"
#include "Player.h"

#include "EnemyTear.h"
#include "Core.h"
#include <EngineCollision.h>
#include "RoomInfo.h"
void Turret::FindStay()
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

	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"Idle");
	}

	if (300.0f >= float4::Len2D(Dir))
	{
		if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
		{
			m_MonsterFSM.ChangeState(L"Attack");
		}
	}
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

}

void Turret::AttackStart()
{
	m_RenderBody->ChangeAnimation(L"Attack");
}

void Turret::AttackStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	if (m_RenderBody->IsEndAni())
	{
		if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
		{
			EngineSound::Play(L"meatheadshoot1.mp3", false, 0);
			EnemyTear* Tear = GetScene()->CreateActor<EnemyTear>();
			Tear->PlayFire(this, Dir, GetRenderBody()->GetPivotPos(), GetPosition(), m_CharacterInfo->GetAtt(), m_CharacterInfo->GetShotSpeed(), 200, false);
			m_CharacterInfo->SetAttackDelay(0.f);
			m_RoomInfo->PushTear(Tear);
		}
		m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

		m_MonsterFSM.ChangeState(L"Find");
	}
	
}

void Turret::DieStart()
{
	m_RenderBody->ChangeAnimation(L"Die");
}

void Turret::DieStay()
{
}

void Turret::DieEnd()
{
}

void Turret::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}

void Turret::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}

void Turret::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}
