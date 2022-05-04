#include "Dinga.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include "Dip.h"
#include "RoomInfo.h"
#include "EnemyDieEffect.h"
#include "PoofEffect.h"
void Dinga::FindStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}
	GetCharacterInfo()->AccelSpeedMove(m_Rad, 5.f);

	if (GetCharacterInfo()->GetAttackDelay() > GetCharacterInfo()->GetAttackDelayMax())
	{
		GetMonsterFSM()->ChangeState(L"Attack");
	}
	GetCharacterInfo()->SetAttackDelay(GetCharacterInfo()->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

}

void Dinga::MoveStart()
{
}


void Dinga::MoveStay()
{
	
}

void Dinga::AttackStart()
{
	m_RenderBody->ChangeAnimation(L"Attack");
	m_RenderHitLayer->ChangeAnimation(L"Attack");
	EngineSound::Play(L"Fart.mp3", false, 0);

}

void Dinga::AttackStay()
{
	if (m_RenderBody->IsEndAni())
	{
		PoofEffect* effect = GetScene()->CreateActor<PoofEffect>();
		effect->SetPosition(GetPosition());


		m_RenderBody->ChangeAnimation(L"Idle");
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_MonsterFSM.ChangeState(L"Find");
		Enemy* Actor = GetScene()->CreateActor<Dip>();
		Actor->SetPosition(GetPosition()+1.f);
		m_RoomInfo->PushEnemy(Actor);
		Actor->SetRoomInfo(m_RoomInfo);
		Actor->On();
		GetCharacterInfo()->SetAttackDelay(0.f);
	}
}

void Dinga::DieStart()
{
	EnemyDieEffect* actor = GetScene()->CreateActor<EnemyDieEffect>();
	actor->SelectPoop();
	actor->SetPosition(GetPosition());
	m_RoomInfo->PushActor(actor);
	EngineSound::Play(L"Death_burst.mp3", false, 0);
	m_RenderHitLayer->RenderOff();

	Death();
	//°¥»öÇÇ
}

void Dinga::DieStay()
{
	
}

void Dinga::DieEnd()
{
}

void Dinga::StartCol(EngineCollision* _This, EngineCollision* _Other)
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
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void Dinga::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Dinga::StayCol(EngineCollision* _This, EngineCollision* _Other)
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
		Dip* dip = dynamic_cast<Dip*>(_Other->GetActor());
		if (dip)
		{
			return;
		}

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

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapObject))
	{
		ColDirStop(Angle);
	}
}
