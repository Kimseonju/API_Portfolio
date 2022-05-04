#include "PlayScene.h"
#include <EngineWindow.h>
#include "Player.h"
#include "MapCollider.h"
#include "Player_ItemCostume.h"
#include "Itemaltar.h"
#include "Item.h"
#include "Door.h"
#include "BonFire.h"
#include "RoomInfo.h"
#include "PlayBackGround.h"
#include "MiniMap.h"
#include "LogicValue.h"

#include "PlayFadeOut.h"
#include "Poop.h"
#include "Stone.h"
#include "Bomb.h"
#include "Core.h"
#include "BossAniActors.h"
#include <EngineTimer.h>

#include "Costume_SadOnion.h"

#include "HPUI.h"
#include "BombUI.h"
#include "CoinUI.h"
#include "KeyUI.h"
#include "BossUI.h"
#include "ControlsBackground.h"
#include <EngineSound.h>

// Static Var
// Static Func

// member Var
PlayScene::PlayScene() :m_MiniMap(nullptr)
, m_BossAniCountMax(3.f), m_BossAniCount(0.f), m_bBossAni(false), m_bossAniActor(nullptr), m_HPUI(nullptr), m_BossUI(nullptr)

{
}

PlayScene::~PlayScene()
{
	for (int y = 0; y < m_Map.size(); ++y)
	{
		for (int x = 0; x < m_Map[y].size(); ++x)
		{
			delete m_Map[y][x];
			m_Map[y][x] = nullptr;
		}
		m_Map[y].clear();
	}
	m_Map.clear();

}
// member Func

void PlayScene::Start()
{
	LogicValue::MainScene = this;
	//맵설정
	{
		//맵에 있는 적들 로드
		RoomInfo::LoadRoom();
		for (int y = 0; y < MapY; ++y)
		{
			std::vector< RoomInfo*> vec;
			vec.reserve(MapX);
			for (int x = 0; x < MapX; ++x)
			{
				RoomInfo* room = new RoomInfo();
				room->Init(float4(x, y), this);
				vec.push_back(room);
			}
			m_Map.push_back(vec);

		}
		//맵설정 하드코딩 (이후 2.2중심으로 방경로탐색하면서 타입설정도전해보기)
		m_Map[0][0]->SetType(LogicValue::RoomType::Room);
		m_Map[0][1]->SetType(LogicValue::RoomType::Room);
		m_Map[0][2]->SetType(LogicValue::RoomType::Room);
		m_Map[0][3]->SetType(LogicValue::RoomType::Space);
		m_Map[0][4]->SetType(LogicValue::RoomType::Space);
		m_Map[0][5]->SetType(LogicValue::RoomType::Space);

		m_Map[1][0]->SetType(LogicValue::RoomType::Space);
		m_Map[1][1]->SetType(LogicValue::RoomType::Room);
		m_Map[1][2]->SetType(LogicValue::RoomType::Room);
		m_Map[1][3]->SetType(LogicValue::RoomType::Room);
		m_Map[1][4]->SetType(LogicValue::RoomType::Room);
		m_Map[1][5]->SetType(LogicValue::RoomType::Space);

		m_Map[2][0]->SetType(LogicValue::RoomType::Treasure);
		m_Map[2][1]->SetType(LogicValue::RoomType::Room);
		m_Map[2][2]->SetType(LogicValue::RoomType::Room);
		m_Map[2][3]->SetType(LogicValue::RoomType::Room);
		m_Map[2][4]->SetType(LogicValue::RoomType::Room);
		m_Map[2][5]->SetType(LogicValue::RoomType::Space);

		m_Map[3][0]->SetType(LogicValue::RoomType::Space);
		m_Map[3][1]->SetType(LogicValue::RoomType::Shop);
		m_Map[3][2]->SetType(LogicValue::RoomType::Room);
		m_Map[3][3]->SetType(LogicValue::RoomType::Room);
		m_Map[3][4]->SetType(LogicValue::RoomType::Space);
		m_Map[3][5]->SetType(LogicValue::RoomType::Space);

		m_Map[4][0]->SetType(LogicValue::RoomType::Secret);
		m_Map[4][1]->SetType(LogicValue::RoomType::Room);
		m_Map[4][2]->SetType(LogicValue::RoomType::Room);
		m_Map[4][3]->SetType(LogicValue::RoomType::Room);
		m_Map[4][4]->SetType(LogicValue::RoomType::Boss);
		m_Map[4][5]->SetType(LogicValue::RoomType::FinalBoss);


		m_Map[5][0]->SetType(LogicValue::RoomType::Space);
		m_Map[5][1]->SetType(LogicValue::RoomType::Space);
		m_Map[5][2]->SetType(LogicValue::RoomType::Space);
		m_Map[5][3]->SetType(LogicValue::RoomType::Space);
		m_Map[5][4]->SetType(LogicValue::RoomType::Space);
		m_Map[5][5]->SetType(LogicValue::RoomType::Space);
		for (int y = 0; y < MapY; ++y)
		{
			for (int x = 0; x < MapX; ++x)
			{
				m_Map[y][x]->Start();
				if (LogicValue::RoomType::Space == m_Map[y][x]->GetType())
					continue;
				PlayBackGround* Object = CreateActor<PlayBackGround>();
				Object->Init(m_Map[y][x]->GetType(), float4(x, y));
			}
		}
		//맵 충돌 오브젝트
		MapCollider* Object = CreateActor<MapCollider>();
		Object->SetPosition(EngineWindow::GetSize().hfloat4());
	}


	{
		//플레이어

		Player* Object = CreateActor<Player>();
		LogicValue::MainPlayer = Object;

		float4 MapCount = Object->GetMapCount();
		ControlsBackground* controlsBackground = CreateActor<ControlsBackground>();
		controlsBackground->Init(MapCount);

	}
	///////////////////////////////////////////UI
	{
		//미니맵
		m_MiniMap = CreateActor<MiniMap>();
		m_MiniMap->MapResize(float4(MapX, MapY));

		//HP
		m_HPUI = CreateActor<HPUI>();
		//CoinUI
		CreateActor<CoinUI>();
		//BombUI
		CreateActor<BombUI>();
		//KeyUI
		CreateActor<KeyUI>();
		//BossUI
		m_BossUI = CreateActor<BossUI>();

	}

	//FadeOut
	CreateActor<PlayFadeOut>();

	//확인오브젝트용
	//Sound


	//충돌설정
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::Enemy));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::Pit));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::Enemy));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::MapObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::EnemyTear));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::Spikes));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::Bomb));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::PlayerItem));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::research));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::BombObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Player), static_cast<int>(LogicValue::CollisionGroup::MapEnemyObject));

	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::Enemy));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::Pit));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::Enemy));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::MapObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::EnemyTear));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::Spikes));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::Bomb));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::PlayerItem));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::research));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::BombObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerHead), static_cast<int>(LogicValue::CollisionGroup::MapEnemyObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Enemy), static_cast<int>(LogicValue::CollisionGroup::MapEnemyObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::PlayerTear), static_cast<int>(LogicValue::CollisionGroup::Enemy));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::ShopItemObject), static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));

	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Bomb), static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));

	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Protection), static_cast<int>(LogicValue::CollisionGroup::EnemyTear));

	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Enemy), static_cast<int>(LogicValue::CollisionGroup::MapObject));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Enemy), static_cast<int>(LogicValue::CollisionGroup::Enemy));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Enemy), static_cast<int>(LogicValue::CollisionGroup::Bomb));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::Enemy), static_cast<int>(LogicValue::CollisionGroup::Pit));

	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::MapObject), static_cast<int>(LogicValue::CollisionGroup::PlayerTear));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::MapObject), static_cast<int>(LogicValue::CollisionGroup::EnemyTear));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::MapObject), static_cast<int>(LogicValue::CollisionGroup::Bomb));
	CollisionGroupLink(static_cast<int>(LogicValue::CollisionGroup::BombObject), static_cast<int>(LogicValue::CollisionGroup::BombObject));

	float4 MapCount = LogicValue::MainPlayer->GetMapCount();
	m_Map[MapCount.iy()][MapCount.ix()]->DoorSoundOff();
}

void PlayScene::SceneUpdate()
{

	//현재 맵 업데이트
	float4 MapCount = LogicValue::MainPlayer->GetMapCount();
	float4 OldMapCount = LogicValue::MainPlayer->GetOldMapCount();

	if (!LogicValue::MainPlayer->IsCamMove())
	{
		m_Map[MapCount.iy()][MapCount.ix()]->Update();
	}

	if (m_bBossAni)
	{
		m_BossAniCount += EngineTimer::MainTimer.GetFDeltaTime();
		if (m_BossAniCount > m_BossAniCountMax)
		{
			m_BossAniCount = 0.f;
			m_bossAniActor->Death();
			m_bBossAni = false;
			LogicValue::MainPlayer->InputOn();
			m_Map[MapCount.iy()][MapCount.ix()]->Play();
		}
	}


	//미니맵
	if (LogicValue::MainPlayer->GetMapMove())
	{
		LogicValue::MainPlayer->SetMapMove(false);
		m_MiniMap->MoveMapRender(MapCount);
		m_Map[OldMapCount.iy()][OldMapCount.ix()]->Stop();
		MiniMapRender();


		if (m_Map[MapCount.iy()][MapCount.ix()]->GetType() == LogicValue::RoomType::Boss)
		{
			if (!m_Map[MapCount.iy()][MapCount.ix()]->GetClear())
			{
				m_bossAniActor = CreateActor<BossAniActors>();
				m_bBossAni = true;
				LogicValue::MainPlayer->InputOff();
				EngineSound::Play(L"bossEnter.mp3", false, 0);
				EngineSound::Stop(L"GameBGM.mp3");
				//Object->BossSet();
			}
		}
		else if (m_Map[MapCount.iy()][MapCount.ix()]->GetType() == LogicValue::RoomType::FinalBoss)
		{
			if (!m_Map[MapCount.iy()][MapCount.ix()]->GetClear())
			{
				m_bossAniActor = CreateActor<BossAniActors>();
				m_bBossAni = true;
				LogicValue::MainPlayer->InputOff();
				m_bossAniActor->BossSet(L"Mom");
				LogicValue::MainPlayer->SetPosition({ MapCount.ix() * 960 + 480, MapCount.iy() * 540 + 270 });
				EngineSound::Play(L"Mom_Vox_Isaac_2.mp3", false, 0);
				EngineSound::Play(L"bossEnter.mp3", false, 0);
				EngineSound::Stop(L"GameBGM.mp3");
				m_Map[MapCount.iy()][MapCount.ix()]->DoorSoundOff();
			}
		}
		else
		{
			m_Map[MapCount.iy()][MapCount.ix()]->Play();
		}
	}

}

void PlayScene::SceneLateUpdate()
{
	float4 MapCount = LogicValue::MainPlayer->GetMapCount();
	float4 OldMapCount = LogicValue::MainPlayer->GetOldMapCount();

	m_Map[MapCount.iy()][MapCount.ix()]->LateUpdate();
	m_Map[OldMapCount.iy()][OldMapCount.ix()]->Update();
	m_Map[OldMapCount.iy()][OldMapCount.ix()]->LateUpdate();

}

void PlayScene::SceneDebugRender()
{
	float4 MapCount = LogicValue::MainPlayer->GetMapCount();
	int size=m_Map[MapCount.iy()][MapCount.ix()]->GetEnemySize();


	int posx = 800;
	int posy = 150;
	EngineString PrintText = L"EnemyCount: ";
	PrintText += size;
	DebugTextout(PrintText, posx, posy);
}

int PlayScene::GetMapCheck(const float4& _Pos)
{
	if (0 > _Pos.ix() || MapX <= _Pos.ix() || 0 > _Pos.iy() || MapY <= _Pos.iy()) //넘어갔을때
		return static_cast<int>(LogicValue::RoomType::Max);
	if (LogicValue::RoomType::Space == m_Map[_Pos.iy()][_Pos.ix()]->GetType()) //방이 빈공간일시
		return static_cast<int>(LogicValue::RoomType::Max);
	else if (LogicValue::RoomType::Secret == m_Map[_Pos.iy()][_Pos.ix()]->GetType())
	{
		//시크릿방일때의 처리
		//클리어상태로 들어갈지 안들어갈지 체크하기
  		RoomInfo* room = m_Map[_Pos.iy()][_Pos.ix()];
		if (!m_Map[_Pos.iy()][_Pos.ix()]->GetClear())
		{
			return static_cast<int>(LogicValue::RoomType::Max);
		}
		else//클리어상태임
		{
			static_cast<int>((m_Map[_Pos.iy()][_Pos.ix()]->GetType()));
		}
	}
	return static_cast<int>((m_Map[_Pos.iy()][_Pos.ix()]->GetType()));
}

int PlayScene::GetMapCheck_Door(const float4& _Pos)
{
	if (0 > _Pos.ix() || MapX <= _Pos.ix() || 0 > _Pos.iy() || MapY <= _Pos.iy()) //넘어갔을때
		return static_cast<int>(LogicValue::RoomType::Max);
	if (LogicValue::RoomType::Space == m_Map[_Pos.iy()][_Pos.ix()]->GetType()) //방이 빈공간일시
		return static_cast<int>(LogicValue::RoomType::Max);
	
	return static_cast<int>((m_Map[_Pos.iy()][_Pos.ix()]->GetType()));
}

bool PlayScene::GetMapClear(const float4& _Pos)
{
	if (!m_Map[_Pos.iy()][_Pos.ix()]->GetClear()) //방이 클리어되지 않았을때
		return false;

	return true;
}

void PlayScene::MiniMapRender()
{
	float4 MapCount = LogicValue::MainPlayer->GetMapCount();
	for (int i = 0; i < 4; ++i)
	{
		float4 CheckMap = MapCount + float4::AllDir[i];
		if (0 > CheckMap.ix() || MapX <= CheckMap.ix() || 0 > CheckMap.iy() || MapY <= CheckMap.iy())
			continue;
		if (static_cast<int>(LogicValue::RoomType::Max) == GetMapCheck(CheckMap))
			continue;
		if (static_cast<int>(LogicValue::RoomType::Space) == GetMapCheck(CheckMap))
			continue;

		m_MiniMap->InputMapRender(CheckMap, m_Map[CheckMap.iy()][CheckMap.ix()]->GetType());

	}
}
