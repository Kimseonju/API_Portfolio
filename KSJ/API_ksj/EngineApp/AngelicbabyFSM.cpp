#include "Angelicbaby.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
void Angelicbaby::FindStay()
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

	if (250.f > float4::Len2D(Dir))
		m_MonsterFSM.ChangeState(L"Move");
}

void Angelicbaby::MoveStart()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	m_CharacterInfo.SetDir(Dir);
}


void Angelicbaby::MoveStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	Dir.Normalize();
	m_CharacterInfo.SetDir(Dir);
	//벽충돌시 추가
}

void Angelicbaby::DieStart()
{
	Enemy::DieStart();
	Off();
}

void Angelicbaby::DieStay()
{

}

void Angelicbaby::DieEnd()
{
}

void Angelicbaby::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == (int)LogicValue::CollisionGroup::PlayerTear)
	{
		m_CharacterInfo.SetHP(m_CharacterInfo.GetHP() - 1);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo.DamageAccel(Dir, 20.f);
	}
	else if (_Other->GetOrder() == (int)LogicValue::CollisionGroup::Bomb)
	{
		m_CharacterInfo.SetHP(m_CharacterInfo.GetHP() - 3);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo.DamageAccel(Dir, 40.f);
	}

	if (m_CharacterInfo.GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Angelicbaby::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Angelicbaby::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == (int)LogicValue::CollisionGroup::Player)
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo.DamageAccel(Dir, 0.8f);
	}

	if (_Other->GetOrder() == (int)LogicValue::CollisionGroup::Enemy)
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo.AccelSpeedMove(Dir, 5.f);
		return;
	}
}
