#include "Host.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include "EnemyTear.h"
#include "RoomInfo.h"
void Host::FindStart()
{
	if (nullptr != m_RenderBody)
	{
		m_RenderBody->ChangeAnimation(L"Idle");
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_bAttackStart = false;
	}
	m_Timer = 0.f;
	m_bFire = false;

	m_Invincible = true;
}
void Host::FindStay()
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

	if (!m_bAttackStart)
	{
		if (300.0f >= float4::Len2D(Dir))
		{
			m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());
			if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax() - 1.f)
			{
				m_MonsterFSM.ChangeState(L"Attack");
				m_Invincible = false;
			}
		}
		//바깥에있으면 초기화
		else
		{
			m_CharacterInfo->SetAttackDelay(0.f);
		}
	}
	
}
void Host::AttackStart()
{
	m_bAttackStart = true;
	m_RenderBody->ChangeAnimation(L"Attack");
	m_RenderHitLayer->ChangeAnimation(L"Attack");
}

void Host::AttackStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	if (!m_bFire)
	{
		if (m_CharacterInfo->GetAttackDelay() > m_CharacterInfo->GetAttackDelayMax())
		{
			float Angle = float4::GetAngle(Dir);
			Angle -= 50.f;

			if (Angle < 0.f)
			{
				Angle += 360.f;
			}
			for (int i = 0; i < 5; ++i)
			{

				float4 ADir = float4::AngleToDir2DDeg(Angle);
				EnemyTear* Tear = GetScene()->CreateActor<EnemyTear>();
				Tear->PlayFire(this, ADir, m_RenderBody->GetPivotPos(), GetPosition(), m_CharacterInfo->GetAtt(), m_CharacterInfo->GetShotSpeed(), 200);
				m_RoomInfo->PushTear(Tear);
				Angle += 25.f;
				if (Angle > 360.f)
				{
					Angle -= 360.f;
				}
			}
			EngineSound::Play(L"meatheadshoot1.mp3", false, 0);


			m_CharacterInfo->SetAttackDelay(0.f);
			m_bFire = true;
		}


		m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());
	}
	else
	{
		m_Timer += EngineTimer::MainTimer.GetFDeltaTime();
		if (m_Timer > 0.5f)
		{
			m_MonsterFSM.ChangeState(L"Find");

		}
	}
	

}

void Host::MoveStart()
{
}


void Host::MoveStay()
{
}

void Host::DieStart()
{
	Enemy::DieStart();
	m_RenderHitLayer->RenderOff();
	Death();
}

void Host::DieStay()
{
	
}

void Host::DieEnd()
{
}

void Host::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (!m_Invincible)
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
	else
	{
		if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
		{
			float4 Dir = _This->GetPosition() - _Other->GetPosition();
			Dir.Normalize();
			m_CharacterInfo->DamageAccel(Dir, 20.f);
		}
		else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
		{
			float4 Dir = _This->GetPosition() - _Other->GetPosition();
			Dir.Normalize();
			m_CharacterInfo->DamageAccel(Dir, 40.f);
		}
	}
	
}

void Host::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Host::StayCol(EngineCollision* _This, EngineCollision* _Other)
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

