#include "MOMBoss.h"
#include "LogicValue.h"
#include <EngineWindowResMgr.h>
#include <EngineCollision.h>
#include "Fly.h"
#include "RoomInfo.h"
#include "Player.h"
#include "EnemyTear.h"
#include "Core.h"
#include "Door.h"
#include <EngineRendererBasic.h>
#include "MomLeg.h"
#include "MomBody.h"
#include <EngineSceneManager.h>
#include "Core.h"
//static
//static func


MOMBoss::MOMBoss() :m_MomLeg(nullptr), m_Timer(0.f), m_EyeTimer(0.f), m_iEye(0), m_LegTimer(0.f)
, m_bPlayerAttack(false)
, m_AttackSoundCount(3.f)
, m_Hit(false)
, m_HitTimer(0.f)
{
}

MOMBoss::~MOMBoss()
{
}

void MOMBoss::Start()
{
	Enemy::Start();


}
void MOMBoss::Init()
{
	GetCharacterInfo()->SetHPMax(50);
	GetCharacterInfo()->SetHP(GetCharacterInfo()->GetHPMax());
	m_MomLeg = GetScene()->CreateActor<MomLeg>();
	m_MomLeg->Init(this);
	m_MomLeg->SetRoomInfo(GetRoomInfo());
	GetRoomInfo()->PushEnemy(m_MomLeg);
	for (int i = 0; i < 4; ++i)
	{
		MomBody* mombody = GetScene()->CreateActor<MomBody>();
		GetRoomInfo()->PushEnemy(mombody);
		EngineString str;
		if (float4::LEFT == float4::AllDir[i])
		{
			str += L"Left";
		}
		if (float4::RIGHT == float4::AllDir[i])
		{
			str += L"Right";
		}
		if (float4::UP == float4::AllDir[i])
		{
			str += L"Up";
		}
		if (float4::DOWN == float4::AllDir[i])
		{
			str += L"Down";
		}
		mombody->Init(str, float4::AllDir[i], this);
		mombody->SetRoomInfo(GetRoomInfo());
		m_MomBody.push_back(mombody);
	}
	m_LegTimer = 5.f;
}


void MOMBoss::Update()
{
	m_Timer += EngineTimer::MainTimer.GetFDeltaTime();
	m_EyeTimer += EngineTimer::MainTimer.GetFDeltaTime();
	m_LegTimer+= EngineTimer::MainTimer.GetFDeltaTime();

	m_AttackSoundCount += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_Hit)
	{
		m_HitTimer+= EngineTimer::MainTimer.GetFDeltaTime();
		if (m_HitTimer < 0.2f)
		{
			for (size_t i = 0; i < m_MomBody.size(); ++i)
			{
				m_MomBody[i]->AllHitRenderOn();
			}
			m_MomLeg->AllHitRenderOn();
		}
		else
		{
			for (size_t i = 0; i < m_MomBody.size(); ++i)
			{
				m_MomBody[i]->AllHitRenderOff();
			}
			m_MomLeg->AllHitRenderOff();
			m_HitTimer = 0.f;
			m_Hit = false;
		}

	}

	if (m_bPlayerAttack)
	{
		EngineSound::Play(L"Mom_Vox_EvilLaugh.mp3", false, 0);
		m_bPlayerAttack = false;
		m_Timer = 2.f;
		m_EyeTimer = 1.f;
		m_LegTimer = 0.f; 
	}

	//3초마다 적있는지 확인
	if (m_Timer > 5.f)
	{
		m_Timer = 0.f;
		//만약 4보다 작다면
		if (m_RoomInfo->GetFinshBossEnemySize() < 8)
		{
			int size= 4 - m_RoomInfo->GetFinshBossEnemySize();
			//바디를 불러낸다.
			for (size_t i = 0; i < size; ++i)
			{
				m_MomBody[i]->Body();
			}
		}
	}
	//1초마다 적있는지 확인
	if (m_EyeTimer>2.f)
	{
		m_EyeTimer = 0.f;
		//만약 3보다 작다면 한곳에 눈을 불러내기
		if (m_RoomInfo->GetFinshBossEnemySize() < 3)
		{
			int size = 4 - m_RoomInfo->GetFinshBossEnemySize();
			
			m_MomBody[m_iEye]->Eye();
			m_iEye++;
			if (m_iEye == 4)
				m_iEye = 0;
		}
	}

	//4초주기로 확인
	if (m_LegTimer > 4.f)
	{
		m_LegTimer = 0.f;
		m_MomLeg->On();
		m_MomLeg->Attack();
		
	}

	if (m_CharacterInfo->GetHP() <= 0)
	{
		//Enemy::DieStart();
		EngineSound::Play(L"Mom_Vox_Death_1.mp3", false, 0);
		EngineSound::Stop(L"Mom_Vox_EvilLaugh.mp3");
		EngineSound::Stop(L"Mom_Vox_Isaac_0.mp3");
		EngineSound::Stop(L"Mom_Vox_Isaac_1.mp3");
		EngineSound::Stop(L"Mom_Vox_Isaac_2.mp3");
		EngineSound::Stop(L"Mom_Vox_Grunt_2.mp3");
		EngineSound::Stop(L"MomFightBGM.mp3");

		Core::SceneManager.ChangeScene(L"EndScene");
		Off();
	}
	
	

}

void MOMBoss::OnTask()
{
	Enemy::OnTask();
	m_MomLeg->On();
	
	for(size_t i=0; i<m_MomBody.size(); ++i)
	{
		m_MomBody[i]->On();
	}
}

void MOMBoss::UpdateNext()
{
}

