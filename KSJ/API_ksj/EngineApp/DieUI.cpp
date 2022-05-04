#include "DieUI.h"
#include <EngineRendererBasic.h>
#include "RoomInfo.h"
#include "Player.h"
#include "LogicValue.h"
//static
//static func

DieUI::DieUI() :m_DieBackground(nullptr), m_DieEnemyImage(nullptr)
, m_Room(nullptr)
{
}

DieUI::~DieUI()
{
}

void DieUI::Start()
{
	m_DieBackground = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::DieUI));
	m_DieBackground->TransCut_Setting(L"DieBackground.bmp", 0);
	m_DieBackground->CamPosOff();
	
	m_DieBackground->SetPivotPos({ EngineWindow::GetSize().hfloat4()});

	m_DieEnemyImage = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::DieUI)+1);
	m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 1);
	m_DieEnemyImage->SetRenderScale({ 128,96 });

	float4 pos = EngineWindow::GetSize().hfloat4();
	pos.x += 66.f;
	pos.y -= 26.f;
	m_DieEnemyImage->SetPivotPos(pos);
	GetScene()->SetPause(true);
	EngineSound::Stop(L"BossBGM.mp3");
	EngineSound::Stop(L"MomFightBGM.mp3");
	EngineSound::Stop(L"GameBGM.mp3");

	EngineSound::Play(L"Died.mp3", true, 10);
	EngineSound::Volume(L"MomFightBGM.mp3", 0.7f);
}


void DieUI::Update()
{

}

void DieUI::UpdateUI()
{
	if (true == EngineInput::IsUp(L"Enter"))
	{
		GetScene()->SetPause(false);
		EngineSound::Stop(L"Died.mp3");
		switch (m_Room->GetType())
		{
		case LogicValue::RoomType::Boss:
			EngineSound::Play(L"BossBGM.mp3", true, 10);
			EngineSound::Volume(L"BossBGM.mp3", 0.7f);
			break;
		case LogicValue::RoomType::FinalBoss:
			EngineSound::Play(L"MomFightBGM.mp3", true, 10);
			EngineSound::Volume(L"MomFightBGM.mp3", 0.7f);
			break;
		default:
			EngineSound::Play(L"GameBGM.mp3", true, 5);
			EngineSound::Volume(L"GameBGM.mp3", 0.7f);

			break;	
		}

		Player* player=LogicValue::MainPlayer;
		player->Die_recovery();
		Death();
	}
}

void DieUI::SetDieEnemyImage(const EngineString& _EnemyStr)
{
	if (_EnemyStr == L"Fly")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 1);
	}
	else if (_EnemyStr == L"Bomb")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 11);
	}
	else if (_EnemyStr == L"BonFire")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 6);
	}
	else if (_EnemyStr == L"Boomfly")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 3);
	}
	else if (_EnemyStr == L"Deathshead")
	{
		//아직 이미지수정안함
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 20);
	}
	else if (_EnemyStr == L"Dinga")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 13);
	}
	else if (_EnemyStr == L"Dip")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 13);
	}
	else if (_EnemyStr == L"FlyBoss")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 19);
	}
	else if (_EnemyStr == L"full_fly")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 14);
	}
	else if (_EnemyStr == L"Horf")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 0);
	}
	else if (_EnemyStr == L"Host")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 10);
	}
	else if (_EnemyStr == L"Moms_hand")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 16);
	}
	else if (_EnemyStr == L"Nerveending")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 17);

	}
	else if (_EnemyStr == L"Onetooth")
	{
		//이미지찾자
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 20);
	}
	else if (_EnemyStr == L"Pooter")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 2);
	}
	else if (_EnemyStr == L"Psychicmaw")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 9);
	}
	else if (_EnemyStr == L"Psychic_horf")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 9);
	}
	else if (_EnemyStr == L"Redboomfly")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 4);
	}
	else if (_EnemyStr == L"Redmaw")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 8);
	}
	else if (_EnemyStr == L"Spikes")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 12);
	}
	else if (_EnemyStr == L"Squirt")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 13);
	}
	else if (_EnemyStr == L"Sucker")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 5);
	}
	else if (_EnemyStr == L"Turret")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 15);
	}
	else if (_EnemyStr == L"Mom")
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 18);
	}
	else
	{
		m_DieEnemyImage->TransCut_Setting(L"death_enemies.bmp", 20);
		EngineDebug::AssertMsg("_EnemyStr==??????? ");
	}
	m_DieEnemyImage->CamPosOff();
}

