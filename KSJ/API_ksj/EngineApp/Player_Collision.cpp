#include "Player.h"
#include <EngineCollision.h>
#include "Poop.h"
#include "Stone.h"
#include "BonFire.h"
#include "Bomb.h"
#include "Enemy.h"
#include "EnemyTear.h"
#include "BombEffect.h"
#include "LogicValue.h"
#include "PickUpItem.h"
#include "EnemyTear.h"
void Player::HeadStartCol(EngineCollision* _This, EngineCollision* _Other)
{

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Enemy))
	{
		if (m_DebugInvincible)
		{
			return;
		}

		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				strDieActor = _Other->GetActor()->GetClassType();
			}
		}
		return;
	}
	

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::EnemyTear))
	{
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				EngineActor* actor = _Other->GetActor();
				EnemyTear* tear=dynamic_cast<EnemyTear*>(actor);
				if (nullptr!=tear)
				{
					strDieActor=tear->GetFireMonster();
				}
			}
		}
		return;
	}
}

void Player::HeadEndCol(EngineCollision* _This, EngineCollision* _Other)
{
	

}

void Player::HeadStayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Enemy))
	{
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				strDieActor = _Other->GetActor()->GetClassType();
			}
		}
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->AccelSpeedMove(Dir, 0.8f);
		return;
	}

	
	
}


void Player::BodyStartCol(EngineCollision* _This, EngineCollision* _Other)
{

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			float4 len=_This->GetPosition() - _Other->GetPosition();
			if (len.Len() == 0)
			{
				return;
			}
			if (m_CharacterInfo->GetHP() <= 0)
			{
				strDieActor = _Other->GetActor()->GetClassType();
			}
			float Angle = float4::GetAngle(_This->GetPosition(), _Other->GetPosition());
			//날아갈 방향
			float4 Dir = float4::AngleToDir2DDeg(Angle);
			m_CharacterInfo->DamageAccel(Dir, 5.f);
		}
	}

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Enemy))
	{
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				strDieActor = _Other->GetActor()->GetClassType();
			}
		}
		return;
	}

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::EnemyTear))
	{
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				EngineActor* actor = _Other->GetActor();
				EnemyTear* tear = dynamic_cast<EnemyTear*>(actor);
				if (nullptr != tear)
				{
					strDieActor = tear->GetFireMonster();
				}
			}
		}
		return;
	}

}

void Player::BodyEndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Player::BodyStayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Spikes))
	{

		if (m_Fly)
			return;
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				strDieActor = _Other->GetActor()->GetClassType();
			}
		}
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Enemy))
	{
		if (m_DebugInvincible)
		{
			return;
		}
		if (!m_Invincible) {
			m_Invincible = true;
			m_State = ePlayerState::DAMAGE;
			m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
			if (m_CharacterInfo->GetHP() <= 0)
			{
				strDieActor = _Other->GetActor()->GetClassType();
			}
		}
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->AccelSpeedMove(Dir, 0.8f);
		return;
	}

	float Angle = float4::GetAngle(_This->GetPosition(), _Other->GetPosition());
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapObject))
	{

		Bomb* bomb = dynamic_cast<Bomb*>(_Other->GetActor());
		if (bomb)
		{
			if (m_bCheckBomb)
			{
				return;
			}
			
		}

		BonFire* bonFire = dynamic_cast<BonFire*>(_Other->GetActor());
		if (bonFire != nullptr)
		{
			if (m_DebugInvincible)
			{
				return;
			}
			if (!m_Invincible) {
				m_Invincible = true;
				m_State = ePlayerState::DAMAGE;
				m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
				if (m_CharacterInfo->GetHP() <= 0)
				{
					strDieActor = _Other->GetActor()->GetClassType();
				}
			}
		}

		if (m_Fly)
			return;

		ColDirStop(Angle);
		return;
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapEnemyObject))
	{
		ColDirStop(Angle);
		return;
	}

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::BombObject))
	{

		ColDirStop(Angle);
		return;
	}

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Pit))
	{
		if (m_Fly)
			return;
		ColDirStop(Angle);
		return;
	}
}




void Player::ColDirStop(float Angle)
{//오른쪽방향
	if (Angle > 315.f || Angle < 44.f)
	{
		if (m_CharacterInfo->GetDir().x != float4::RIGHT.x)
		{
			m_CharacterInfo->StopX();
		}

	}
	//왼쪽
	else if (Angle > 136.f && Angle < 224.f)
	{
		if (m_CharacterInfo->GetDir().x != float4::LEFT.x)
		{
			m_CharacterInfo->StopX();
		}
	}
	//위

	else if (Angle > 226.f && 314.f > Angle)
	{
		if (m_CharacterInfo->GetDir().y != float4::UP.y)
		{
			m_CharacterInfo->StopY();
		}
	}
	//아래
	else if (Angle > 46.f && 134.f > Angle) {

		if (m_CharacterInfo->GetDir().y != float4::DOWN.y)
			m_CharacterInfo->StopY();
	}
}

