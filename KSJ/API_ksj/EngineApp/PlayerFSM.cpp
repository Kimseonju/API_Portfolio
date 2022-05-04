#include "Player.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include <list>
#include "Player_ItemCostume.h"
#include "Tears.h"
#include "LogicValue.h"
#include <EngineCollision.h>
#include "Item.h"
#include "Familiar.h"
#include "LogicValue.h"
#include "RoomInfo.h"
#include "PlayScene.h"
#include "DieUI.h"
void Player::BodyIDLEStart()
{
	ChangeBodyAnimation(L"Idle");
	if (ePlayerState::DAMAGE != m_State
		&& ePlayerState::DIE != m_State)
		m_State = ePlayerState::IDLE;
}

void Player::BodyIDLEStay()
{
	if (ePlayerState::DAMAGE != m_State
		&& ePlayerState::DIE != m_State)
		m_State = ePlayerState::IDLE;

	if (
		true == EngineInput::IsPress(L"L") ||
		true == EngineInput::IsPress(L"R") ||
		true == EngineInput::IsPress(L"U") ||
		true == EngineInput::IsPress(L"D")
		)
	{
		m_BodyFSM.ChangeState(L"MOVE");
	}
}

void Player::BodyMOVEStart()
{
}

void Player::BodyMOVEStay()
{
	if (ePlayerState::DAMAGE != m_State
		&& ePlayerState::DIE != m_State)
		m_State = ePlayerState::MOVE;
	//지금 현재 맵충돌로 움직임 수정해야대는뎁..
	if (
		true == EngineInput::IsFree(L"L") &&
		true == EngineInput::IsFree(L"R") &&
		true == EngineInput::IsFree(L"U") &&
		true == EngineInput::IsFree(L"D")
		)
	{
		m_BodyFSM.ChangeState(L"IDLE");
	}
	else
	{
		ChangeBodyAnimation(L"Move");
	}
}

void Player::HeadIDLEStart()
{
	ChangeHeadAnimation(L"Idle");
}

void Player::HeadIDLEStay()
{
	ChangeHeadAnimation(L"Idle");
	if (
		(true == EngineInput::IsPress(L"LFire") ||
		true == EngineInput::IsPress(L"RFire") ||
		true == EngineInput::IsPress(L"UFire") ||
		true == EngineInput::IsPress(L"DFire"))
		&& m_Input
		)
	{
		m_HeadFSM.ChangeState(L"FIRE");
	}
}

void Player::HeadFIREStart()
{
	ChangeHeadAnimation(L"Fire");
}

void Player::HeadFIREStay()
{
	if (ePlayerState::DAMAGE != m_State)
		m_State = ePlayerState::ATTACK;
	if (
		true == EngineInput::IsFree(L"LFire") &&
		true == EngineInput::IsFree(L"RFire") &&
		true == EngineInput::IsFree(L"UFire") &&
		true == EngineInput::IsFree(L"DFire")
		)
	{
		m_HeadFSM.ChangeState(L"IDLE");
		int size = static_cast<int>(m_Familiar.size());
		for (int i = 0; i < size; ++i)
		{
			m_Familiar[i]->ChangeAnimationdir(L"DownIdle");
		}
	}
	else
	{
		ChangeHeadAnimation(L"Fire");
		ChangeFamiliarAnimation(L"Fire");
		if (m_CharacterInfo->GetAttackDelayMax() < m_CharacterInfo->GetAttackDelay() && m_State != ePlayerState::DAMAGE)
		{


			m_CharacterInfo->SetAttackDelay(0.f);

			float shot = m_MultiShotRange / m_MultiShot;
			float4 fdir;
			fdir = float4::AllDir[static_cast<int>(m_HeadDir)];
			int leftshot = m_MultiShot / 2;

			for (int i = 0; i < m_MultiShot; ++i)
			{
				//좌우공격
				float4 vecShot = float4::ZERO;
				if (fdir.x != 0.f && fdir.y == 0.f)
				{
					vecShot.y += ((shot * leftshot) - (shot * i));
				}
				//위아래공격
				else if (fdir.y != 0.f && fdir.x == 0.f)
				{
					vecShot.x += ((shot * leftshot) - (shot * i));
				}
				Tears* Tear = GetScene()->CreateActor<Tears>();
				fdir = (fdir + (m_CharacterInfo->GetDir() * 0.5f));
				fdir.Normalize();
				float4 pos = GetPosition();

				pos += vecShot;

				Tear->PlayFire(this, fdir, float4::ZERO, pos, m_CharacterInfo->GetAtt(), m_CharacterInfo->GetShotSpeed(), m_CharacterInfo->GetShotRange(), m_bGuided);

				RoomInfo* room = LogicValue::MainScene->GetMap(m_MapCount.ix(), m_MapCount.iy());

				Tear->SetRoom(room);
			}


			EngineSound::Play(L"TearFire.mp3", false, 0);
		}

		int size = static_cast<int>(m_Familiar.size());
		float4 familiardir;
		familiardir = float4::AllDir[static_cast<int>(m_HeadDir)];
		for (int i = 0; i < size; ++i)
		{
			m_Familiar[i]->FireEvent(familiardir);
		}


		//플레이어가 공격하고있으면 패밀리어도 공격

	//패밀리어들 조작


	}

}



void Player::EmotionIDLEStart()
{
}

void Player::EmotionIDLEStay()
{
	m_RenderEmotion->Off();
	if (m_CharacterInfo->GetHP() <= 0)
	{
		m_State = ePlayerState::DIE;
	}

	if (ePlayerState::DIE == m_State)
	{
		m_EmotionFSM.ChangeState(L"DIE");
		//죽는 사운드 출력
		EngineSound::Play(L"hurt3.mp3", false, 0);
		EngineSound::Volume(L"hurt3.mp3", 0.5f);
	}

	else if (ePlayerState::DAMAGE == m_State)
	{
		m_EmotionFSM.ChangeState(L"DAMAGE");
		EngineSound::Play(L"hurt3.mp3", false, 0);
		EngineSound::Volume(L"hurt3.mp3", 0.5f);
	}

	else if (m_Itemfunction != nullptr)
	{
		m_bCollectionItem = true;
		m_EmotionFSM.ChangeState(L"ITEM");
	}
}

void Player::EmotionDAMAGEStart()
{
	m_RenderEmotion->ChangeAnimation(L"Damage");
	m_RenderEmotion->On();
	m_RenderHead->Off();
	m_RenderBody->Off();
	m_Invincible = true;
	//std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	//std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	//for (; start != end; ++start)
	//{
	//	(*start)->FirstAnimationdir(L"DownIdle");
	//}
	m_DamageAni = true;

	m_DamageOnOffCount = 0.f;


}

void Player::EmotionDAMAGEStay()
{//데미지입은상태라면

	m_DamageOnOffCount += EngineTimer::MainTimer.GetFDeltaTime();

	//무적이 1/3시간이 지났다
	if (m_GracePeriod > 0.3f && m_DamageAni)
	{
		m_RenderEmotion->ChangeAnimation(L"Idle");
		m_RenderEmotion->Off();
		m_RenderHead->On();
		m_RenderBody->On();
		std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
		std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
		for (; start != end; ++start)
		{
			(*start)->FirstAnimationclear();
			(*start)->On();
		}
		m_State = ePlayerState::IDLE;
		m_DamageAni = false;
	}

	if (m_DamageOnOffCount > m_DamageOnOffCountMax)
	{

		if (ePlayerState::DAMAGE == m_State)
		{
			if (m_view)
			{
				m_RenderEmotion->On();
				m_RenderHead->Off();
				m_RenderBody->Off();
			}
			else
			{
				m_RenderEmotion->Off();
				m_RenderHead->Off();
				m_RenderBody->Off();
			}
		}
		if (ePlayerState::DAMAGE != m_State)
		{
			if (m_view)
			{
				m_RenderEmotion->Off();
				m_RenderHead->On();
				m_RenderBody->On();
			}
			else
			{
				m_RenderEmotion->Off();
				m_RenderHead->Off();
				m_RenderBody->Off();
			}

		}

		std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
		std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
		for (; start != end; ++start)
		{
			if (m_view)
			{
				(*start)->On();
			}
			else
			{
				(*start)->Off();
			}
		}


		m_view = !m_view;

		m_DamageOnOffCount = 0.f;



	}



	if (true == m_Invincible)
	{
		m_GracePeriod += EngineTimer::FDeltaTime();

	}
	//데미지안입는시간이 다 지났다면
	if (m_GracePeriodMax < m_GracePeriod)
	{
		m_DamageOnOffCount = 0.f;
		m_RenderHead->On();
		m_RenderBody->On();

		std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
		std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
		for (; start != end; ++start)
		{
			(*start)->On();
		}
		m_State = ePlayerState::IDLE;

		m_Invincible = false;
		m_GracePeriod = 0.f;
		m_EmotionFSM.ChangeState(L"IDLE");
		m_view = false;
	}
}

void Player::EmotionItemStart()
{
	m_RenderEmotion->ChangeAnimation(L"Item");
	m_RenderEmotion->On();
	m_RenderHead->Off();
	m_RenderBody->Off();
	std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	for (; start != end; ++start)
	{
		(*start)->Off();
	}
}

void Player::EmotionItemStay()
{
	if (m_RenderEmotion->IsEndAni())
	{
		//아이템에있는 함수실행
		m_Itemfunction();
		m_Itemfunction = nullptr;
		m_bCollectionItem = false;
		//애니메이션 눈물공격속도에 따른 업데이트
		SetHeadAnimFrameTimer(GetCharacterInfo()->GetAttackDelayMax() / 2);

		m_RenderEmotion->ChangeAnimation(L"Idle");
		m_RenderEmotion->Off();
		m_RenderHead->On();
		m_RenderBody->On();
		std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
		std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
		for (; start != end; ++start)
		{
			(*start)->On();
		}

		m_EmotionFSM.ChangeState(L"IDLE");
	}
}

void Player::EmotionDieStart()
{
	InputOff();
	EngineSound::Play(L"dies.mp3", false, 0);
	m_CharacterInfo->StopSpeed();

	m_BodyCol->Off();
	m_HeadCol->Off();
	m_CharacterInfo->StopSpeed();
	m_RenderEmotion->ChangeAnimation(L"Die");
	m_RenderEmotion->On();
	m_RenderHead->Off();
	m_RenderBody->Off();
	std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	for (; start != end; ++start)
	{
		(*start)->Off();
	}
}

void Player::EmotionDieStay()
{
	if (m_RenderEmotion->IsEndAni())
	{
		DieUI* dieui = GetScene()->CreateActor< DieUI>();

		dieui->SetDieEnemyImage(strDieActor);
		RoomInfo* room = LogicValue::MainScene->GetMap(m_MapCount.ix(), m_MapCount.iy());
		dieui->SetRoomInfo(room);
		strDieActor = L"";

	}
}
