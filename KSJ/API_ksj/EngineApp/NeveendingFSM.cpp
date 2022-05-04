#include "Nerveending.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
void Nerveending::FindStay()
{
}

void Nerveending::MoveStart()
{
}


void Nerveending::MoveStay()
{
}

void Nerveending::DieStart()
{
	Enemy::DieStart();
	m_RenderHitLayer->RenderOff();
	Death();
}

void Nerveending::DieStay()
{
	
}

void Nerveending::DieEnd()
{
}

void Nerveending::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
	float Angle = float4::GetAngle(_This->GetPosition(), _Other->GetPosition());
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapObject))
	{
		ColDirStop(Angle);
	}
}

void Nerveending::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Nerveending::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}
