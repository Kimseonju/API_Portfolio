#include "Fly.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
void Fly::FindStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}
	if (nullptr != m_Target)
	{
		m_Angle += EngineTimer::FDeltaTime(60.f);
		float4 Dir = float4::AngleToDir2DDeg(m_Angle);
		SetPosition(Dir * 40.0f);
		return;
	}
	else
	{
		GetCharacterInfo()->AccelSpeedMove(m_Rad, 1.f);
		float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

		if (250.f > float4::Len2D(Dir))
			m_MonsterFSM.ChangeState(L"Move");
	}
}

void Fly::MoveStart()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	m_CharacterInfo->SetDir(Dir);
}


void Fly::MoveStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	Dir.Normalize();
	m_CharacterInfo->SetDir(Dir);
	//벽충돌시 추가
}

void Fly::DieStart()
{
	Enemy::DieStart();
	m_RenderBody->ChangeAnimation(L"Die");
	m_Collision->Off();
}

void Fly::DieStay()
{
	GetCharacterInfo()->StopSpeed();
	m_RenderHitLayer->RenderOff();
	if (m_RenderBody->IsEndAni())
	{
		Death();
	}
}

void Fly::DieEnd()
{
}

void Fly::StartCol(EngineCollision* _This, EngineCollision* _Other)
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

void Fly::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Fly::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
}
