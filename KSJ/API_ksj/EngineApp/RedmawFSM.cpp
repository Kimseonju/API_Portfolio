#include "Redmaw.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include "EnemyTear.h"
#include "RoomInfo.h"
void Redmaw::FindStay()
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

void Redmaw::MoveStart()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();
	Dir.Normalize();

	m_CharacterInfo->SetDir(Dir);
}


void Redmaw::MoveStay()
{
	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	Dir.Normalize();
	m_CharacterInfo->SetDir(Dir);
	//벽충돌시 추가
}

void Redmaw::DieStart()
{
	Enemy::DieStart();

	EngineSound::Play(L"meatheadshoot1.mp3", false, 0);
	for (int i = 0; i < 4; ++i)
	{
		EnemyTear* Tear = GetScene()->CreateActor<EnemyTear>();
		Tear->PlayFire(this, float4::AllDir[i], m_RenderBody->GetPivotPos(), GetPosition(), m_CharacterInfo->GetAtt(), m_CharacterInfo->GetShotSpeed(), 200);
		m_RoomInfo->PushTear(Tear);
	}

	m_RenderHitLayer->RenderOff();
	Death();
}

void Redmaw::DieStay()
{
	
}

void Redmaw::DieEnd()
{
}

void Redmaw::StartCol(EngineCollision* _This, EngineCollision* _Other)
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

void Redmaw::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Redmaw::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapObject))
	{
		ColDirStop(Angle);
	}
}
