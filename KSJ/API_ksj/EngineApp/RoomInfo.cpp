
#include "PlayScene.h"
#include "RoomInfo.h"
#include <EngineActor.h>
#include "Door.h"
#include <EngineRendererAnim.h>
#include <EngineWindowResMgr.h>
#include <EngineFile.h>
#include <map>
#include <corecrt_io.h>

#include <EngineWindow.h>

#include "LogicValue.h"

//아이템
#include "Itemaltar.h"
#include "Item.h"

//맵오브젝트헤더
#include "Poop.h"
#include "Stone.h"
#include "Bomb.h"
#include "BonFire.h"

//적헤더
#include "Fly.h"
#include "Pooter.h"
#include "FlyBoss.h"
#include "Boomfly.h"
#include "full_fly.h"
#include "Deathshead.h"
#include "Nerveending.h"
#include "Psychicmaw.h"
#include "Psychic_horf.h"
#include "Onetooth.h"
#include "Redboomfly.h"
#include "Horf.h"

#include "Dinga.h"
#include "Dip.h"
#include "Host.h"
#include "Moms_hand.h"
#include "Redmaw.h"
#include "Squirt.h"
#include "Sucker.h"
#include "Turret.h"
#include "RoomEditorBackground.h"
#include <EngineInput.h>
#include "Enemy.h"
#include <EngineFile.h>
#include <typeinfo>

#include "BossUI.h"

//Grid

#include "Spikes.h"
#include "PitLeftTop.h"
#include "PitTop.h"
#include "PitRightTop.h"
#include "PitLeft.h"
#include "PitCenter.h"
#include "PitRight.h"
#include "PitLeftBottom.h"
#include "PitBottom.h"
#include "PitRightBottom.h"
#include "MOMBoss.h"

#include "PoofEffect.h"
#include "ShopItem.h"

#include <EngineDirectory.h>
#include <EngineFile.h>
#include "PickUpItem.h"
#include "Player.h"
#include "BoxItem.h"
//static
LogicValue::RoomInfoGroup RoomInfo::RoomInfoGroups = LogicValue::RoomInfoGroup::Room1;
LogicValue::BossType RoomInfo::BossSelectCount = LogicValue::BossType::flyBoss;
std::map<LogicValue::RoomInfoGroup, std::vector<std::pair<LogicValue::EditorActorType, float4>>> RoomInfo::m_AllRoomInfoActor;
//static func

void RoomInfo::LoadRoom()
{
	EngineFile	pFile;
	EngineDirectory Dir;
	std::vector<EngineFile> File;

	Dir.MoveParent(L"API_ksj");
	Dir.MoveChild(L"Res");
	Dir.MoveChild(L"Data");
	Dir.MoveChild(L"RoomEnemyType");
	File = Dir.DirectoryAllFileToVector(L"*.data");

	//= L"RoomEnemyInfo.data";
	//std::string Path = str.GetConvertMultiByte(CP_UTF8);

	pFile.m_Str = File[0].c_str();

	//EngineString FileName = EnginePath::IOName(_Path);

	//pFile.m_Str = L"..\\Res\\Data\\RoomEnemyType\\RoomEnemyInfo.data";

	

	//모든방을 만든다.
	for (int room = 0; room < static_cast<int>(LogicValue::RoomInfoGroup::Max); ++room)
	{
		if (m_AllRoomInfoActor.end() == m_AllRoomInfoActor.find((LogicValue::RoomInfoGroup)room))
		{
			m_AllRoomInfoActor.insert(std::map<LogicValue::RoomInfoGroup, std::vector<std::pair<LogicValue::EditorActorType, float4>>>::value_type((LogicValue::RoomInfoGroup)room, std::vector<std::pair<LogicValue::EditorActorType, float4>>()));
		}
	}
	//파일이 없으면 종료
	if (_access(pFile.GetConvertMultiByte().c_str(), 0) != 0) {
		return;
	}
	pFile.Open(L"rb");

	
	//방은 이미 다 생성했으므로 다 남아있음 바로불러오기
	for (int RoomGroup = 0; RoomGroup < static_cast<int>(LogicValue::RoomInfoGroup::Max); ++RoomGroup)
	{
		int Size = 0;
		pFile.Read(&Size, sizeof(int), sizeof(int), 1);
		m_AllRoomInfoActor[(LogicValue::RoomInfoGroup)RoomGroup].reserve((size_t)Size);

		for (int i = 0; i < Size; ++i)
		{
			int itype = 99;
			pFile.Read(&itype, sizeof(int), sizeof(int), 1);
	
			float4 pos;
			pFile.Read(&pos, sizeof(float4), sizeof(float4), 1);
			if (itype == 99)
			{
				EngineDebug::AssertMsg("if (itype == 99)");
			}
			LogicValue::EditorActorType type = (LogicValue::EditorActorType)itype;
	
			m_AllRoomInfoActor[(LogicValue::RoomInfoGroup)RoomGroup].push_back(std::make_pair(type, pos));
		}
	}
	pFile.Close();
}


RoomInfo::RoomInfo() : m_Type(LogicValue::RoomType::Max), m_Clear(true), m_MapCount(float4::ZERO), m_Scene(nullptr)
, m_Boss(nullptr), m_ItemPosCount(0)
, m_bSoundClose(false)
, m_bSoundOpen(false)
, m_bDropItem(false)
, m_LeftDoor(nullptr)
, m_RightDoor(nullptr)
, m_UpDoor(nullptr)
, m_DownDoor(nullptr)
{}
RoomInfo::~RoomInfo()
{
}
void RoomInfo::PushEnemy(Enemy* _Enemy)
{
	m_AllEnemy.push_back(_Enemy);
}
void RoomInfo::PushFinshBossEnemy(Enemy* _Enemy)
{
	m_AllEnemyInvincibility.push_back(_Enemy);
}
void RoomInfo::PushActor(EngineActor* _Actor)
{
	m_AllObejct.push_back(_Actor);
}
void RoomInfo::PushTear(EngineActor* _Actor)
{
	m_AllTear.push_back(_Actor);
}



void RoomInfo::Init(const float4& _MapCount, PlayScene* _Scene)
{
	m_MapCount = _MapCount;
	m_Scene = _Scene;


	if (m_MapCount.x == 2.f && m_MapCount.y == 2.f)
	{
		m_bDropItem = true;
	}
}
void RoomInfo::Start()
{
	if (nullptr == m_Scene)
	{
		EngineDebug::AssertMsg("if (nullptr == m_Scene)");
	}
	float4 MapSize = EngineWindow::GetSize();

	for (int i = 0; i < 4; ++i)
	{
		float4 CheckMap = m_MapCount + float4::AllDir[i];
		if (0 > CheckMap.ix() || MapX <= CheckMap.ix() || 0 > CheckMap.iy() || MapY <= CheckMap.iy())
			continue;
		if (static_cast<int>(LogicValue::RoomType::Max)==m_Scene->GetMapCheck_Door(CheckMap))
			continue;
		Door* Object = m_Scene->CreateActor<Door>();
		Object->SetPosition({ (MapSize.ix() * m_MapCount.ix())+ MapSize.ihx() + (410 * float4::AllDir[i].ix()), (MapSize.iy() * m_MapCount.iy())+ MapSize.ihy() + (200 * float4::AllDir[i].iy()) });
		if (LogicValue::RoomType::Boss == m_Type)
		{
			Object->SetDoorImage(static_cast<int>(LogicValue::RoomType::Boss), float4::AllDir[i]);
		}
		else if(LogicValue::RoomType::Treasure == m_Type)
		{
			Object->SetDoorImage(static_cast<int>(LogicValue::RoomType::Treasure), float4::AllDir[i]);
		}
		else if (LogicValue::RoomType::FinalBoss == m_Type)
		{
			Object->SetDoorImage(static_cast<int>(LogicValue::RoomType::Boss), float4::AllDir[i]);
			Object->Off();
		}
		else if (LogicValue::RoomType::Secret == m_Type)
		{
			Object->SetDoorImage(static_cast<int>(LogicValue::RoomType::Secret), float4::AllDir[i]);
			Object->Off();
		}
		else
		{
			Object->SetDoorImage(m_Scene->GetMapCheck_Door(CheckMap), float4::AllDir[i]);
		}
		m_Door.push_back(Object);
		if (float4::LEFT == float4::AllDir[i])
		{
			m_LeftDoor = Object;
		}
		else if (float4::RIGHT == float4::AllDir[i])
		{
			m_RightDoor = Object;
		}
		else if (float4::UP == float4::AllDir[i])
		{

			m_UpDoor = Object;
		}
		else if (float4::DOWN == float4::AllDir[i])
		{
			m_DownDoor = Object;
		}
	}

	if (LogicValue::RoomType::Room == m_Type)
	{

		for (int i = 0; i<m_AllRoomInfoActor[RoomInfoGroups].size(); ++i)
		{
			LogicValue::EditorActorType type = m_AllRoomInfoActor[RoomInfoGroups][i].first;
			float4 pos = m_AllRoomInfoActor[RoomInfoGroups][i].second;

			EngineActor* pActor = nullptr;
			Enemy* EnemyActor = nullptr;

			switch (type)
			{
			case LogicValue::EditorActorType::Fly:
			{
				EnemyActor = m_Scene->CreateActor<Fly>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}

			case LogicValue::EditorActorType::Pooter:

			{
				EnemyActor = m_Scene->CreateActor<Pooter>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Boomfly:
			{
				EnemyActor = m_Scene->CreateActor<Pooter>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::full_fly:
			{
				EnemyActor = m_Scene->CreateActor<full_fly>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Deathshead:
			{
				EnemyActor = m_Scene->CreateActor<Deathshead>();
				m_AllEnemyInvincibility.push_back(EnemyActor);
				break;
			}

			case LogicValue::EditorActorType::Nerveending:
			{
				EnemyActor = m_Scene->CreateActor<Nerveending>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}

			case LogicValue::EditorActorType::Psychicmaw:
			{
				EnemyActor = m_Scene->CreateActor<Psychicmaw>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Psychic_horf:
			{
				EnemyActor = m_Scene->CreateActor<Psychic_horf>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Onetooth:
			{
				EnemyActor = m_Scene->CreateActor<Onetooth>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Redboomfly:
			{
				EnemyActor = m_Scene->CreateActor<Redboomfly>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Bomb:
			{
				pActor = m_Scene->CreateActor<Bomb>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::BonFire:
			{
				pActor = m_Scene->CreateActor<BonFire>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::Poop:
			{
				pActor = m_Scene->CreateActor<Poop>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::Stone:
			{
				pActor = m_Scene->CreateActor<Stone>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::Horf:
			{
				EnemyActor = m_Scene->CreateActor<Horf>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Dinga:
			{
				EnemyActor = m_Scene->CreateActor<Dinga>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Dip:
			{
				EnemyActor = m_Scene->CreateActor<Dip>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Host:
			{
				EnemyActor = m_Scene->CreateActor<Host>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Moms_hand:
			{
				EnemyActor = m_Scene->CreateActor<Moms_hand>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Redmaw:
			{
				EnemyActor = m_Scene->CreateActor<Redmaw>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Squirt:
			{
				EnemyActor = m_Scene->CreateActor<Squirt>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Sucker:
			{
				EnemyActor = m_Scene->CreateActor<Sucker>();
				m_AllEnemy.push_back(EnemyActor);
				break;
			}
			case LogicValue::EditorActorType::Turret:
			{
				EnemyActor = m_Scene->CreateActor<Turret>();
				m_AllEnemyInvincibility.push_back(EnemyActor);
				break;
			}

			case LogicValue::EditorActorType::Spikes:
			{
				pActor = m_Scene->CreateActor<Spikes>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitLeftTop:
			{
				pActor = m_Scene->CreateActor<PitLeftTop>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitTop:
			{
				pActor = m_Scene->CreateActor<PitTop>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitRightTop:
			{
				pActor = m_Scene->CreateActor<PitRightTop>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitLeft:
			{
				pActor = m_Scene->CreateActor<PitLeft>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitCenter:
			{
				pActor = m_Scene->CreateActor<PitCenter>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitRight:
			{
				pActor = m_Scene->CreateActor<PitRight>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitLeftBottom:
			{
				pActor = m_Scene->CreateActor<PitLeftBottom>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitBottom:
			{
				pActor = m_Scene->CreateActor<PitBottom>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::PitRightBottom:
			{
				pActor = m_Scene->CreateActor<PitRightBottom>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::BoxItem:
			{
				pActor = m_Scene->CreateActor<BoxItem>();
				m_AllObejct.push_back(pActor);
				break;
			}
			case LogicValue::EditorActorType::MAX:
				break;
			default:
				break;
			}

			if (pActor != nullptr)
			{
				pActor->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
				pActor->MovePosition(pos);
			}
			if (EnemyActor != nullptr)
			{
				EnemyActor->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
				EnemyActor->MovePosition(pos);
				EnemyActor->SetRoomInfo(this);
			}
			//pActor->SetSize({ 30.f,30.f });
		}

		NextRoomInfo();
		m_Clear = false;


		if (m_MapCount == float4{ 2.f, 3.f })
		{
			EngineActor* pActor = m_Scene->CreateActor<PitLeftTop>();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f -48.f , m_MapCount.iy() * MapSize.iy() + 210.f });
			m_AllObejct.push_back(pActor);
			for (int i = 0; i < 8; ++i)
			{
				pActor = m_Scene->CreateActor<PitTop>();
				pActor->SetPosition({ m_MapCount.ix() * MapSize.ix()+330.f+(48.f*i), m_MapCount.iy() * MapSize.iy()+210.f });


				m_AllObejct.push_back(pActor);

			}
			pActor = m_Scene->CreateActor<PitRightTop>();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f + (48.f * 8) , m_MapCount.iy() * MapSize.iy() + 210.f });

			pActor = m_Scene->CreateActor<PitLeft>();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f - 48.f , m_MapCount.iy() * MapSize.iy() + 260.f });
			for (int i = 0; i < 8; ++i)
			{
				if (i ==3)
					continue;
				pActor = m_Scene->CreateActor<PitCenter>();
				pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f + (48.f * i), m_MapCount.iy() * MapSize.iy() + 260.f });
				m_AllObejct.push_back(pActor);
			}
			pActor = m_Scene->CreateActor<PitRight>();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f + (48.f * 8) , m_MapCount.iy() * MapSize.iy() + 260.f });


			pActor = m_Scene->CreateActor<PitLeftBottom>();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f - 48.f , m_MapCount.iy() * MapSize.iy() + 310.f });
			for (int i = 0; i < 8; ++i)
			{
				pActor = m_Scene->CreateActor<PitBottom>();
				pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f + (48.f * i), m_MapCount.iy() * MapSize.iy() + 310.f });
				m_AllObejct.push_back(pActor);
			}
			pActor = m_Scene->CreateActor<PitRightBottom>();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 330.f + (48.f * 8) , m_MapCount.iy() * MapSize.iy() + 310.f });


		}
	}

	if (LogicValue::RoomType::Boss==m_Type)
	{
		FlyBoss* pActor = nullptr;
		pActor = m_Scene->CreateActor<FlyBoss>();
		m_Boss = pActor;

		pActor->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
		pActor->MovePosition({ 480,270 });
		pActor->SetRoomInfo(this);
		m_AllEnemy.push_back(pActor);
		m_Clear = false;
	}
	if (LogicValue::RoomType::Secret == m_Type)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				PickUpItem* pActor = nullptr;
				pActor = m_Scene->CreateActor<PickUpItem>();
				pActor->Init(LogicValue::ItemType::Coin);
				pActor->SetPosition({ m_MapCount.ix() * MapSize.ix() + 360 + 80 * i, m_MapCount.iy() * MapSize.iy() + 200 + 70 * j });
				pActor->Off();
				m_AllItem.push_back(pActor);
			}
		}
		m_Clear = false;
		m_bDropItem = true;
	}

	if (LogicValue::RoomType::Treasure == m_Type)
	{
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m_ItemPos.push_back(float4({ 200+ i * 100, 130+ j * 128 }));
			}
		}
		m_bDropItem = true;

		//Itemaltar* pActor = nullptr;
		//pActor = m_Scene->CreateActor<Itemaltar>();
		//pActor->SetPosition({ m_MapCount.ix() * MapSize.ix()+MapSize.ihx(), m_MapCount.iy() * MapSize.iy() + MapSize.ihy() });
		//pActor->Off();
		//m_AllItem.push_back(pActor);
		for (size_t i = 0; i < 15; ++i)
		{
			float4 MapSize = EngineWindow::GetSize();
			EngineActor* Actor;
			Actor = m_Scene->CreateActor<Itemaltar>();
			Actor->SetPosition({ m_MapCount.ix() * MapSize.ix() + m_ItemPos[i].ix(), m_MapCount.iy() * MapSize.iy() + m_ItemPos[i].iy() });
			//m_ItemPosCount++;
			//if (m_ItemPos.size() <= m_ItemPosCount)
			//{
			//	m_ItemPosCount = 0;
			//}
		}
	}

	//엄마보스임
	//여기서 생성
	if (LogicValue::RoomType::FinalBoss== m_Type)
	{
		//MOMBoss는 가운데에두고 그 안에 생성된 나머지 오브젝트들이 알아서 위치함
		MOMBoss* momboss = m_Scene->CreateActor<MOMBoss>();
		m_Boss = momboss;
		momboss->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
		momboss->MovePosition({ 480,270 });
		momboss->SetRoomInfo(this);
		momboss->Init();
		m_AllEnemy.push_back(momboss);
		m_Clear = false;
		m_bDropItem = true;
	}

	if (LogicValue::RoomType::Shop == m_Type)
	{
		m_bDropItem = true;
		{
			ShopItem* pActor = nullptr;
			pActor = m_Scene->CreateActor<ShopItem>();
			pActor->Init(LogicValue::ItemType::Bomb);
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
			pActor->MovePosition({ 300,300 });
			pActor->Off();
			m_AllItem.push_back(pActor);
		}
		{
			ShopItem* pActor = nullptr;
			pActor = m_Scene->CreateActor<ShopItem>();
			pActor->Init(LogicValue::ItemType::Heart);
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
			pActor->MovePosition({ 400,300 });
			pActor->Off();
			m_AllItem.push_back(pActor);
		}
		{
			ShopItem* pActor = nullptr;
			pActor = m_Scene->CreateActor<ShopItem>();
			pActor->Init();
			pActor->SetPosition({ m_MapCount.ix() * MapSize.ix(), m_MapCount.iy() * MapSize.iy() });
			pActor->MovePosition({ 500,300 });
			pActor->Off();
			m_AllItem.push_back(pActor);
		}
	}

	{
		std::list<EngineActor*>::iterator iter = m_AllObejct.begin();
		std::list<EngineActor*>::iterator iterEnd = m_AllObejct.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Off();
		}
		for (int i = 0; i < m_Door.size(); ++i)
		{
			m_Door[i]->Off();
		}

	}


}

void RoomInfo::Play()
{
	//{
	//	std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
	//	std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
	//	for (; iter != iterEnd;)
	//	{
	//		if (false == (*iter)->IsDeath())
	//		{
	//			++iter;
	//			continue;
	//		}
	//		iter = m_AllEnemy.erase(iter);
	//	}
	//}
	//{
	//	std::list<EngineActor*>::iterator iter = m_AllObejct.begin();
	//	std::list<EngineActor*>::iterator iterEnd = m_AllObejct.end();
	//	for (; iter != iterEnd;)
	//	{
	//		if (false == (*iter)->IsDeath())
	//		{
	//			++iter;
	//			continue;
	//		}
	//		iter = m_AllObejct.erase(iter);
	//	}
	//}

	
	for (int i = 0; i < static_cast<int>(m_AllItem.size()); ++i)
	{
		m_AllItem[i]->On();
	}
	for (int i = 0; i < m_Door.size(); ++i)
	{
		if (m_Door[i]->GetRoomType() == LogicValue::RoomType::Secret)
		{
			if (!m_Door[i]->SecretCheck())
			{
				continue;
			}
		}
		m_Door[i]->On();
	}
	{
		std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
		std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->On();
		}
	}
	{
		std::list<EngineActor*>::iterator iter = m_AllObejct.begin();
		std::list<EngineActor*>::iterator iterEnd = m_AllObejct.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->On();
		}
	}
	{
		std::list<Enemy*>::iterator iter = m_AllEnemyInvincibility.begin();
		std::list<Enemy*>::iterator iterEnd = m_AllEnemyInvincibility.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->On();
		}
	}
	

	if (m_Boss)
	{
		m_Scene->GetBossUI()->On();
	}

	if (!m_AllEnemy.empty())
	{
		if (LogicValue::RoomType::FinalBoss == m_Type)
			return;
		if (LogicValue::RoomType::Boss == m_Type)
			return;
		std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
		std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
		for (; iter != iterEnd; ++iter)
		{
			EngineActor* actor=m_Scene->CreateActor< PoofEffect>();
			actor->SetPosition((*iter)->GetPosition());
		}

		EngineSound::Play(L"summon.mp3", false, 0);
		EngineSound::Play(L"doorClose.mp3", false, 0);
	}

}

void RoomInfo::Stop()
{
	for (int i = 0; i < static_cast<int>(m_AllItem.size()); ++i)
	{
		m_AllItem[i]->Off();
	}
	{
		std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
		std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
		for (; iter != iterEnd;)
		{
			if (true == (*iter)->IsDeath())
			{
				iter = m_AllEnemy.erase(iter);
				continue;
			}
			(*iter)->Off();
			++iter;
		}
	}

	{
		std::list<EngineActor*>::iterator iter = m_AllObejct.begin();
		std::list<EngineActor*>::iterator iterEnd = m_AllObejct.end();
		for (; iter != iterEnd;)
		{
			if (true == (*iter)->IsDeath())
			{
				iter = m_AllObejct.erase(iter);
				continue;
			}
			(*iter)->Off();
			++iter;
		}
	}

	{
		//테스트필요
		std::list<EngineActor*>::iterator iter = m_AllTear.begin();
		std::list<EngineActor*>::iterator iterEnd = m_AllTear.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Off();
		}
		m_AllTear.clear();
		
	}
	
		for (int i = 0; i < m_Door.size(); ++i)
		{
			m_Door[i]->Off();
		}


	if (m_Boss)
	{
		m_Scene->GetBossUI()->Off();
	}
}

void RoomInfo::Update()
{
	if (LogicValue::RoomType::Boss == m_Type)
	{
		if (m_Boss != nullptr)
		{
			float HP = static_cast<float>(m_Boss->GetCharacterInfo()->GetHP());
			float HPMAX = static_cast<float>(m_Boss->GetCharacterInfo()->GetHPMax());
			HP /= HPMAX;
			m_Scene->GetBossUI()->SetPercentBar(HP);
			if (m_Boss->IsDeath())
			{
				m_Scene->GetBossUI()->Off();
				m_Boss = nullptr;
			}

		}
	}
	if (LogicValue::RoomType::FinalBoss == m_Type)
	{
		if (m_Boss != nullptr)
		{
			float HP = static_cast<float>(m_Boss->GetCharacterInfo()->GetHP());
			float HPMAX = static_cast<float>(m_Boss->GetCharacterInfo()->GetHPMax());
			HP /= HPMAX;
			m_Scene->GetBossUI()->SetPercentBar(HP);
			if (m_Boss->IsDeath())
			{
				m_Scene->GetBossUI()->Off();
				m_Boss = nullptr;
			}

		}
	}

	if (LogicValue::RoomType::Treasure == m_Type)
	{
		//if (true == EngineInput::IsUp(L"Item"))
		//{
		//	for (size_t i = 0; i < 15; ++i)
		//	{
		//		float4 MapSize = EngineWindow::GetSize();
		//		EngineActor* Actor;
		//		Actor = m_Scene->CreateActor<Itemaltar>();
		//		Actor->SetPosition({ m_MapCount.ix() * MapSize.ix() + m_ItemPos[i].ix(), m_MapCount.iy() * MapSize.iy() + m_ItemPos[i].iy() });
		//		//m_ItemPosCount++;
		//		//if (m_ItemPos.size() <= m_ItemPosCount)
		//		//{
		//		//	m_ItemPosCount = 0;
		//		//}
		//	}
		//	
		//}
	}
}

void RoomInfo::LateUpdate()
{

	{
		std::list<EngineActor*>::iterator iter = m_AllObejct.begin();
		std::list<EngineActor*>::iterator iterEnd = m_AllObejct.end();
		for (; iter != iterEnd;)
		{
			if (false == (*iter)->IsDeath())
			{
				++iter;
				continue;
			}
			iter = m_AllObejct.erase(iter);
		}
	}
	{
		std::list<EngineActor*>::iterator iter = m_AllTear.begin();
		std::list<EngineActor*>::iterator iterEnd = m_AllTear.end();
		for (; iter != iterEnd;)
		{
			//매우 신기한 코드네여기
			if (false == (*iter)->IsDeath())
			{
				++iter;
				continue;
			}
			//++iter;
			iter = m_AllTear.erase(iter);
		}
	}

	{
		std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
		std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
		for (; iter != iterEnd;)
		{
			if (false == (*iter)->IsDeath())
			{
				++iter;
				continue;
			}
			iter = m_AllEnemy.erase(iter);
		}
	}
	{
		if (LogicValue::RoomType::FinalBoss== m_Type)
		{
			std::list<Enemy*>::iterator iter = m_AllEnemyInvincibility.begin();
			std::list<Enemy*>::iterator iterEnd = m_AllEnemyInvincibility.end();
			for (; iter != iterEnd; )
			{
				if (false == (*iter)->IsDeath())
				{
					++iter;
					continue;
				}

				iter = m_AllEnemyInvincibility.erase(iter);
			}
		}
	}
	if (0 != m_AllEnemy.size())
	{
		for (int i = 0; i < m_Door.size(); ++i)
		{
			m_Door[i]->SetOpen(false);
		}

		m_bSoundClose = true;
	}
	else
	{
		m_Clear = true;
		std::list<Enemy*>::iterator iter = m_AllEnemyInvincibility.begin();
		std::list<Enemy*>::iterator iterEnd = m_AllEnemyInvincibility.end();
		for (; iter != iterEnd;++iter)
		{
			if (true == (*iter)->IsDeath())
			{
				continue;
			}
			(*iter)->FSMDiePlay();
		}
		m_AllEnemyInvincibility.clear();

		for (int i = 0; i < m_Door.size(); ++i)
		{
			m_Door[i]->SetOpen(true);
		}
		if (!m_bSoundOpen)
		{
			EngineSound::Play(L"doorOpen.mp3", false, 0);
			m_bSoundOpen = true;

		}

		if (!m_bDropItem)
		{
			PickUpItem* dropitem = m_Scene->CreateActor<PickUpItem>();
			dropitem->Init();
			m_AllObejct.push_back(dropitem);

			float4 MapSize = EngineWindow::GetSize();
			dropitem->SetPosition({ m_MapCount.ix() * MapSize.ix() + MapSize.ihx(), m_MapCount.iy() * MapSize.iy()+ MapSize.ihy() });
			//플레이어에게 맵은 클리어가되었다고 보내기
			Player* player=LogicValue::MainPlayer;
			player->SetMapClear(true);
		}
		m_bDropItem = true;
	}
	if (m_Boss)
	{
		if (m_Boss->IsDeath())
		{
			m_Boss = nullptr;
		}
	}
}

void RoomInfo::EnemyAllKill()
{
	std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
	std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->GetCharacterInfo()->SetHP(0);
	}
	m_AllEnemy.clear();
}

Enemy* RoomInfo::TargetEnemyFind(EngineActor* _Other)
{
	Enemy* Return=nullptr;
	float len = 300.f;
	std::list<Enemy*>::iterator iter = m_AllEnemy.begin();
	std::list<Enemy*>::iterator iterEnd = m_AllEnemy.end();
	for (; iter != iterEnd; ++iter)
	{
		float4 pos=(_Other->GetPosition() - (*iter)->GetPosition());
		float checklen = abs(pos.Len());
		if (len > checklen)
		{

			if (LogicValue::RoomType::FinalBoss == m_Type)
			{
				if (m_Boss == (*iter))
					continue;
			}
			if (!(*iter)->IsOn())
			{
				continue;
			}
			Return = (*iter);
			len = checklen;
		}
	}

	return Return;
}
