#include "MomLeg.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
#include <EngineRendererBasic.h>
#include "MOMBoss.h"
void MomLeg::FindStart()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	//플레이어와 씬이 다르면 플레이하는 상태가 아니다.
	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}
	m_Time = 0.f;
}
void MomLeg::FindStay()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	//플레이어와 씬이 다르면 플레이하는 상태가 아니다.
	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}


	float4 Dir = LogicValue::MainPlayer->GetPosition() - GetPosition();

	Dir.Normalize();
	m_CharacterInfo->SetDir(Dir*2);

	if (m_Attack)
	{
		if (!m_bAttackSound)
		{
			m_bAttackSound = true;

			if (m_AttackSoundCount == 0)
			{
				EngineSound::Play(L"Mom_Vox_Isaac_0.mp3", false, 0);
				m_AttackSoundCount++;
			}
			else if (m_AttackSoundCount == 1)
			{
				EngineSound::Play(L"Mom_Vox_Isaac_1.mp3", false, 0);
				m_AttackSoundCount++;
			}
			else if (m_AttackSoundCount == 2)
			{
				EngineSound::Play(L"Mom_Vox_Isaac_2.mp3", false, 0);
				m_AttackSoundCount = 0;
			}
		}
		
		m_AttackTimer += EngineTimer::MainTimer.GetFDeltaTime();

		if (m_AttackTimer >= 2.5f)
		{
			m_CharacterInfo->SetDir(float4::ZERO);
			m_CharacterInfo->StopSpeed();
		}
		if (m_AttackTimer >= 3.f)
		{
			m_MonsterFSM.ChangeState(L"Attack");
		}
	}
	

}

void MomLeg::MoveStart()
{
	m_Time -=2.5f;
	m_RenderUpdate = true;
	m_RenderUpdateCheck = false;
	m_bAttackInSound = false;
}


void MomLeg::MoveStay()
{

	m_Time += EngineTimer::FDeltaTime();

	float4 PivotPos = float4::ZERO;
	if (m_OldPivot != float4::ZERO)
		PivotPos = m_OldPivot;
	else
		PivotPos = m_Leg->GetPivotPos();
	MoveRenderUpdate(PivotPos);
	if (m_Time < 1.f)
	{
		m_CollisionBody->Off();
		float4 fPivotPos = m_Leg->GetPivotPos();
		float4 CurPos = float4::Lerp2DMax(fPivotPos, { 50,-1000 }, m_Time);
		m_Leg->SetPivotPos(CurPos);
		m_OldPivot = CurPos;
	}
	

	else
	{
		m_MonsterFSM.ChangeState(L"Find");
		m_Attack = false;
		m_AttackPlay = false;
		Off();
	}

}

void MomLeg::AttackStart()
{
	m_Time = 0.f;
	m_CharacterInfo->StopSpeed();
	m_AttackTimer = 0.f;
	m_RenderUpdateCheck = false;
	m_bAttackSound = false;
}

void MomLeg::AttackStay()
{
	//타임속도조절하기

	//충돌체와 이미지 위치 초기위치는 x 0 y -1000
	//-값을 0으로바꾸면서 떨어지는 느낌주기

	m_Time += EngineTimer::FDeltaTime();
	if (m_Time > 0.2f)
	{
		m_Collision->On();
	}
	if (m_Time > 1.f)
	{
		m_CollisionBody->On();
		m_Collision->Off();
	}
	if (m_Time > 0.2f&& m_Time<0.3f)
	{
		if (!m_RenderUpdateCheck)
		{
			m_RenderUpdate = true;
			if (!m_bAttackInSound)
			{
				m_bAttackInSound = true;

				EngineSound::Play(L"Mom_Vox_Grunt_2.mp3", false, 0);
				
			}
		}
		
	}
	if (m_Time < 1.f)
	{
		float4 PivotPos = float4::ZERO;
		if(m_OldPivot!=float4::ZERO)
			PivotPos = m_OldPivot;
		else
			PivotPos = m_Leg->GetPivotPos();

		float4 CurPos = float4::Lerp2DMax(PivotPos, { 50,-300 }, m_Time);
		m_Leg->SetPivotPos(CurPos);
		MoveRenderUpdate(CurPos);
	}
	else
	{

		if(m_Time>2.5f)
			m_MonsterFSM.ChangeState(L"Move");
	}



}



void MomLeg::DieStart()
{
	//Enemy::DieStart();
	Death();
}

void MomLeg::DieStay()
{

}

void MomLeg::DieEnd()
{
}

void MomLeg::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player)
		|| _Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerHead))
	{
		m_MOMBoss->PlayerAttack();
	}
}

void MomLeg::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void MomLeg::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void MomLeg::BodyStartCol(EngineCollision* _This, EngineCollision* _Other)
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

void MomLeg::BodyEndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void MomLeg::BodyStayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
