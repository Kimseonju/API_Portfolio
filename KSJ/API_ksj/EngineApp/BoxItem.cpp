#include "BoxItem.h"
#include <EngineRendererAnim.h>
#include <EngineCollision.h>
#include "Player.h"
#include "PickUpItem.h"
//static
//static func

LogicValue::ItemBoxType BoxItem::sType = LogicValue::ItemBoxType::Treasure_box;


BoxItem::BoxItem() :
	m_RenderBody(nullptr)
	, m_Collision(nullptr)
	, m_ItemType(LogicValue::ItemBoxType::Max)
	, m_KeyCount(1)
	, m_Open(false)
	, m_CharacterInfo(nullptr)
	, m_WallCollision(Dir::MAX)
	, m_FSMTimer(0.f)
{
}

BoxItem::~BoxItem()
{
	if (m_CharacterInfo)
		delete m_CharacterInfo;
	m_CharacterInfo = nullptr;
}

void BoxItem::Start()
{
	SetClassType(L"BoxItem");
	m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));
	m_Collision->AddStartEvent(this, &BoxItem::StartCol);
	m_Collision->AddStayEvent(this, &BoxItem::StayCol);
	m_Collision->AddEndEvent(this, &BoxItem::EndCol);
	SetSize({ 50.f,50.f });
	m_CharacterInfo = new CCharacterInfo();

	m_Collision->SetScale(GetSize());



	m_ItemType = sType;
	m_RenderBody->SetRenderScale({ 64,64 });
	switch (m_ItemType)
	{
	case LogicValue::ItemBoxType::Treasure_box:
		m_RenderBody->CreateAnimation(L"Idle", L"pickup_chests.bmp", 6, 6, 0.1f);
		m_RenderBody->CreateAnimation(L"Spawn", L"pickup_chests.bmp", 8, 9, 0.1f, false);
		m_RenderBody->CreateAnimation(L"Open", L"pickup_chests.bmp", 7, 7, 0.1f, false);
		break;
	case LogicValue::ItemBoxType::BombAttack_box:
		m_RenderBody->CreateAnimation(L"Idle", L"BombAttackBox.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Spawn", L"BombAttackBox.bmp", 0, 0, 0.1f, false);
		m_RenderBody->CreateAnimation(L"Open", L"BombAttackBox.bmp", 1, 1, 0.1f, false);
		break;
	case LogicValue::ItemBoxType::Max:
		EngineDebug::AssertMsg("case LogicValue::ItemBoxType::Treasure_box:");
		break;
	default:
		break;
	}
	m_RenderBody->ChangeAnimation(L"Spawn");
	TypeNext();
	m_BoxItemFSM.CreateState(L"Spawn", this, &BoxItem::SpawnStay, &BoxItem::SpawnStart, &BoxItem::SpawnEnd);
	m_BoxItemFSM.CreateState(L"Idle", this, &BoxItem::IdleStay, &BoxItem::IdleStart, &BoxItem::IdleEnd);
	m_BoxItemFSM.CreateState(L"Open", this, &BoxItem::OpenStay, &BoxItem::OpenStart, &BoxItem::OpenEnd);
	m_BoxItemFSM.ChangeState(L"Spawn");


}

void BoxItem::Update()
{
	m_BoxItemFSM.Update();
	if (!m_Open)
	{
		if (m_KeyCount <= 0)
		{
			for (int i = 0; i < 10; ++i)
			{
				PickUpItem* item = GetScene()->CreateActor<PickUpItem>();
				item->Init();
				item->SetPosition(GetPosition());
			}
			EngineSound::Play(L"chest_open.mp3", false, 0);
			m_BoxItemFSM.ChangeState(L"Open");
			m_Open = true;
		}
	}
}

void BoxItem::UpdateNext()
{
	m_CharacterInfo->Update();
	MapCollision();
	MovePosition(m_CharacterInfo->GetUpdateSpeed());
}



void BoxItem::MapCollision()
{
	m_WallCollision = Dir::MAX;
	float4 pos = GetPosition();
	pos += m_CharacterInfo->GetUpdateSpeed();

	pos.x = static_cast<float>(pos.ix() % 960);
	pos.y = static_cast<float>(pos.iy() % 540);
	int Left = pos.ix() - GetSize().ihx();
	int Right = pos.ix() + GetSize().ihx();
	int Up = pos.iy() - GetSize().ihy();
	int Down = pos.iy() + GetSize().ihy();
	if (Left + m_CharacterInfo->GetUpdateSpeed().ix() < 102)
	{
		m_WallCollision = Dir::LEFT;
		if (m_CharacterInfo->GetDir().x != 1.f)
			m_CharacterInfo->StopX();
	}
	if (Right + m_CharacterInfo->GetUpdateSpeed().ix() > 850)
	{
		m_WallCollision = Dir::RIGHT;
		if (m_CharacterInfo->GetDir().x != -1.f)
			m_CharacterInfo->StopX();
	}

	if (Up + m_CharacterInfo->GetUpdateSpeed().iy() < 101)
	{
		m_WallCollision = Dir::UP;
		if (m_CharacterInfo->GetDir().y != 1.f)
			m_CharacterInfo->StopY();
	}
	if (Down + m_CharacterInfo->GetUpdateSpeed().iy() > 435)
	{
		m_WallCollision = Dir::DOWN;
		if (m_CharacterInfo->GetDir().y != -1.f)
			m_CharacterInfo->StopY();
	}
}
