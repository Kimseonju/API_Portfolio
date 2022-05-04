#include "Pooter.h"
#include "LogicValue.h"
#include "Player.h"

#include "EnemyTear.h"
#include "Core.h"
#include <EngineCollision.h>
#include "RoomInfo.h"
void Pooter::FindStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	//플레이어와 씬이 다르면 플레이하는 상태가 아니다.
	if (LogicValue::MainPlayer->GetScene() !=Core::SceneManager.GetCurScene())
	{
		return;
	}

	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"Idle");
		m_RenderHitLayer->ChangeAnimation(L"Idle");
	}

	GetCharacterInfo()->AccelSpeedMove(m_Rad, 1.5f);

	if (300.0f >= float4::Len2D(Dir) )
	{

		Dir.Normalize();
		m_CharacterInfo->SetDir(Dir);

		if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
		{
			m_MonsterFSM.ChangeState(L"Attack");
		}
	}
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay()+EngineTimer::MainTimer.GetFDeltaTime());

}

void Pooter::AttackStart()
{
}

void Pooter::AttackStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	m_RenderBody->ChangeAnimation(L"Attack");
	m_RenderHitLayer->ChangeAnimation(L"Attack");

	if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
	{
		EnemyTear* Tear = GetScene()->CreateActor<EnemyTear>();
		Tear->PlayFire(this, Dir, m_RenderBody->GetPivotPos(), GetPosition(), m_CharacterInfo->GetAtt(), m_CharacterInfo->GetShotSpeed(), 200);
		m_CharacterInfo->SetAttackDelay(0.f);
		m_RoomInfo->PushTear(Tear);

		EngineSound::Play(L"TearFire.mp3", false, 0);
	}
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

	m_MonsterFSM.ChangeState(L"Find");
}

void Pooter::DieStart()
{
	m_CharacterInfo->StopSpeed();
	EngineSound::Play(L"Death_burst.mp3", false, 0);
	m_RenderBody->ChangeAnimation(L"Die");
	m_Collision->Off();
	m_RenderHitLayer->RenderOff();
}

void Pooter::DieStay()
{
	m_CharacterInfo->StopSpeed();
	if (m_RenderBody->IsEndAni())
	{
		Death();
	}
}

void Pooter::DieEnd()
{
}

void Pooter::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		float4 Dir = _This->GetPosition()- _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 20.f);

		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP()-3);
		float4 Dir = _This->GetPosition()- _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 40.f);
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Pooter::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
}

void Pooter::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}
