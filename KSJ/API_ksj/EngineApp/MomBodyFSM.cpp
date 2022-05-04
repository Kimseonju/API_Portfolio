#include "MomBody.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include <EngineRendererBasic.h>
#include "MOMBoss.h"
void MomBody::FindStart()
{

}
void MomBody::FindStay()
{

}

void MomBody::MoveStart()
{
}


void MomBody::MoveStay()
{

}

void MomBody::AttackStart()
{
}

void MomBody::AttackStay()
{
}



void MomBody::DieStart()
{
	//Enemy::DieStart();
	Death();
}

void MomBody::DieStay()
{

}

void MomBody::DieEnd()
{
}

void MomBody::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_MOMBoss->GetCharacterInfo()->SetHP(m_MOMBoss->GetCharacterInfo()->GetHP() - 1);
		m_MOMBoss->Hit();
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player)
		|| _Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerHead))
	{
		m_MOMBoss->PlayerAttack();
	}
}

void MomBody::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void MomBody::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
void MomBody::ResearchStartCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void MomBody::ResearchEndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void MomBody::ResearchStayCol(EngineCollision* _This, EngineCollision* _Other)
{
	//손을 내밀게하는 패턴을 바로 실행하기

	//손내밀고나서도 충돌중이라면 타이머가 지나가면 또 내밀기
	if (!m_Hand)
	{
		m_Pattern = 0;
		m_Hand = true;
		m_Body = false;
		m_Eye = false;
		m_BodyTimer = 0.f;
		m_EyeTimer = 0.f;
		m_Render_MomEye->Off();
		m_Render_MomBody->Off();

		m_Render_MomHand->ChangeAnimation(L"Attack");
		m_Render_MomHandLayerHit->ChangeAnimation(L"Attack");

	}

}


