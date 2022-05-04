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
	//���� ���а��ϴ� ������ �ٷ� �����ϱ�

	//�ճ��а����� �浹���̶�� Ÿ�̸Ӱ� �������� �� ���б�
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


