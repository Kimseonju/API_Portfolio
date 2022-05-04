#include "Squirt.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include "EnemyDieEffect.h"

#include "RoomInfo.h"
void Squirt::FindStart()
{
	if (nullptr != m_RenderBody)
	{
		if (0.f <= m_Dir.x)
		{
			m_RenderBody->ChangeAnimation(L"RightIdle");
			m_RenderHitLayer->ChangeAnimation(L"RightIdle");
		}
		else
		{
			m_RenderBody->ChangeAnimation(L"LeftIdle");
			m_RenderHitLayer->ChangeAnimation(L"LeftIdle");
		}
	}
		
}

void Squirt::FindStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}

	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	if (350.f > float4::Len2D(Dir))
		m_MonsterFSM.ChangeState(L"Move");
}

void Squirt::MoveStart()
{
	if (0.f <= m_Dir.x)
	{
		m_RenderBody->ChangeAnimation(L"RightAttack");
		m_RenderHitLayer->ChangeAnimation(L"RightAttack");
	}
	else
	{
		m_RenderBody->ChangeAnimation(L"LeftAttack");
		m_RenderHitLayer->ChangeAnimation(L"LeftAttack");
	}
}


void Squirt::MoveStay()
{
	if (m_RenderBody->IsEndAni())
	{
		m_MonsterFSM.ChangeState(L"Attack");
	}
	
	//벽충돌시 추가
}

void Squirt::AttackStart()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();
	m_CharacterInfo->SetDir(Dir);
	m_Dir = Dir;
	m_CharacterInfo->SetMaxSpeed(500.f);
}

void Squirt::AttackStay()
{
	m_CharacterInfo->SetMaxSpeed(m_CharacterInfo->GetMaxSpeed() - (m_CharacterInfo->GetSpeed() * EngineTimer::MainTimer.GetFDeltaTime()));

	m_CharacterInfo->SetDir(m_Dir);

	if (m_WallCollision == Dir::LEFT)
	{
		m_Dir.x += 1.f;
		m_CharacterInfo->StopSpeed();
	}
	if (m_WallCollision == Dir::RIGHT)
	{
		m_Dir.x += -1.f;
		m_CharacterInfo->StopSpeed();
	}
	if (m_WallCollision == Dir::UP)
	{
		m_Dir.y += 1.f;
		m_CharacterInfo->StopSpeed();
	}
	if (m_WallCollision == Dir::DOWN)
	{
		m_Dir.y -= 1.f;
		m_CharacterInfo->StopSpeed();
	}

	if (0.f <= m_Dir.x)
	{
		m_RenderBody->ChangeAnimation(L"RightAttacking");
		m_RenderHitLayer->ChangeAnimation(L"RightAttacking");
	}
	else
	{
		m_RenderBody->ChangeAnimation(L"LeftAttacking");
		m_RenderHitLayer->ChangeAnimation(L"LeftAttacking");
	}

	if (m_CharacterInfo->GetMaxSpeed() <= 2.f)
	{
		m_CharacterInfo->SetMaxSpeed(0.f);
		m_MonsterFSM.ChangeState(L"Find");
	}
}

void Squirt::DieStart()
{
	EnemyDieEffect* actor = GetScene()->CreateActor<EnemyDieEffect>();
	actor->SetPosition(GetPosition());
	actor->SelectPoop();
	m_RoomInfo->PushActor(actor);
	EngineSound::Play(L"Death_burst.mp3", false, 0);

	m_RenderHitLayer->RenderOff();
	Death();
}

void Squirt::DieStay()
{
	
}

void Squirt::DieEnd()
{
}

void Squirt::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 10.f);
		m_RenderHitLayer->RenderOn();

	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 20.f);
		m_RenderHitLayer->RenderOn();
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Squirt::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Squirt::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
		m_CharacterInfo->AccelSpeedMove(Dir, 5.f);
		return;
	}
	
	float Angle = float4::GetAngle(_This->GetPosition(), _Other->GetPosition());
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Pit))
	{
		ColDirStop(Angle);
	}
}
