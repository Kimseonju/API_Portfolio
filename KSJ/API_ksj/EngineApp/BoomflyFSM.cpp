#include "Boomfly.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include "BombEffect.h"

void Boomfly::MoveStart()
{
}


void Boomfly::MoveStay()
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

void Boomfly::DieStart()
{

	BombEffect* bombeffect = GetScene()->CreateActor<BombEffect>();
	bombeffect->SetPosition(GetPosition());
	m_RenderHitLayer->RenderOff();

	this->Death();
}

void Boomfly::DieStay()
{
}

void Boomfly::DieEnd()
{
}

void Boomfly::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 0.f);
		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 30.f);
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Boomfly::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Boomfly::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
