#include "Horf.h"
#include "LogicValue.h"
#include "Player.h"

#include "EnemyTear.h"
#include "Core.h"
#include <EngineCollision.h>
#include "RoomInfo.h"
void Horf::FindStay()
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
		m_RenderHitLayer->ChangeAnimation(L"Idle");
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

void Horf::AttackStart()
{
	m_RenderBody->ChangeAnimation(L"Attack");
	m_RenderHitLayer->ChangeAnimation(L"Attack");
}

void Horf::AttackStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	m_RenderBody->ChangeAnimation(L"Attack");
	m_RenderHitLayer->ChangeAnimation(L"Attack");

	if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
	{
		EngineSound::Play(L"meatheadshoot1.mp3", false, 0);
		EnemyTear* Tear = GetScene()->CreateActor<EnemyTear>();
		Tear->PlayFire(this, Dir, GetRenderBody()->GetPivotPos(), GetPosition(), m_CharacterInfo->GetAtt(), m_CharacterInfo->GetShotSpeed(), 200);
		m_RoomInfo->PushTear(Tear);

		m_CharacterInfo->SetAttackDelay(0.f);
	}
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

	m_MonsterFSM.ChangeState(L"Find");
}

void Horf::DieStart()
{
	Enemy::DieStart();
	m_RenderHitLayer->RenderOff();

	Death();
}

void Horf::DieStay()
{
}

void Horf::DieEnd()
{
}

void Horf::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 20.f);
		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 40.f);
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Horf::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player)
		|| _Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerHead))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 0.8f);
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Enemy))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->AccelSpeedMove(Dir, 2.f);
		return;
	}
	float Angle = float4::GetAngle(_This->GetPosition(), _Other->GetPosition());
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapObject))
	{
		ColDirStop(Angle);
	}
}

void Horf::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}
