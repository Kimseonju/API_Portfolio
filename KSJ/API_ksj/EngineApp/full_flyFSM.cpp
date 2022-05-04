#include "full_fly.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
void full_fly::FindStay()
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

	GetCharacterInfo()->AccelSpeedMove(m_Rad, 2.f);

	if (250.f > float4::Len2D(Dir))
		m_MonsterFSM.ChangeState(L"Move");
}

void full_fly::MoveStart()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	m_CharacterInfo->SetDir(Dir);
}


void full_fly::MoveStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	Dir.Normalize();
	m_CharacterInfo->SetDir(Dir);
	//벽충돌시 추가
}

void full_fly::DieStart()
{
	Enemy::DieStart();
	m_Collision->Off();
	m_RenderHitLayer->RenderOff();
	Death();
}

void full_fly::DieStay()
{
}

void full_fly::DieEnd()
{
}

void full_fly::StartCol(EngineCollision* _This, EngineCollision* _Other)
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

void full_fly::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void full_fly::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
