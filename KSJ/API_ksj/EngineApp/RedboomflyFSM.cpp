#include "Redboomfly.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include "BombEffect.h"
#include "EnemyTear.h"
#include "RoomInfo.h"
void Redboomfly::MoveStart()
{
}


void Redboomfly::MoveStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		m_CharacterInfo->SetDir(0.f);
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		m_CharacterInfo->SetDir(0.f);
		return;
	}
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
}

void Redboomfly::DieStart()
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
	this->Death();
}

void Redboomfly::DieStay()
{
}

void Redboomfly::DieEnd()
{
}

void Redboomfly::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
		m_RenderHitLayer->RenderOn();
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Redboomfly::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Redboomfly::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
