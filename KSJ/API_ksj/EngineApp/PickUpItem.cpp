#include "PickUpItem.h"
#include <EngineRendererAnim.h>
#include <EngineCollision.h>
#include "Player.h"
//static
//static func

bool PickUpItem::Heart = false;

LogicValue::ItemType PickUpItem::sType= LogicValue::ItemType::Bomb;
PickUpItem::PickUpItem():
	m_RenderBody(nullptr)
	, m_Collision(nullptr)
	, m_ItemType(LogicValue::ItemType::Max)
	, m_Count(1)
	, m_Idle(true)
	, m_bCollision(false)
	, m_CharacterInfo(nullptr)
	, m_WallCollision(Dir::MAX)
	, m_Time(0.f)
	, m_PickSound(false)
{
}

PickUpItem::~PickUpItem()
{
	if(m_CharacterInfo)
		delete m_CharacterInfo;
	m_CharacterInfo = nullptr;
}

void PickUpItem::Start()
{
	m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));
	m_Collision->AddStartEvent(this, &PickUpItem::StartCol);
	m_Collision->AddStayEvent(this, &PickUpItem::StayCol);
	m_Collision->AddEndEvent(this, &PickUpItem::EndCol);
	SetSize({ 32.f,32.f });
	m_CharacterInfo = new CCharacterInfo();

	m_Collision->SetScale(GetSize());
}

void PickUpItem::Update()
{
	m_Time += EngineTimer::MainTimer.GetFDeltaTime();
	if (!m_PickSound)
	{

		if (m_ItemType == LogicValue::ItemType::Coin)
		{
			EngineSound::Play(L"Coindrop.mp3", false, 0);
		}
			
		m_PickSound = true;
	}
	
	if (!m_Idle && m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"Idle");
		m_Idle = true;
	}
	if (m_bCollision && m_RenderBody->IsEndAni())
	{
		Death();
	}
}

void PickUpItem::UpdateNext()
{
	m_CharacterInfo->Update();
	MapCollision();
	MovePosition(m_CharacterInfo->GetUpdateSpeed());
}

void PickUpItem::Init(LogicValue::ItemType _ItemType)
{
	m_ItemType = _ItemType;
	Create();
}

void PickUpItem::Init()
{
	m_ItemType = sType;
	TypeNext();
	if (m_ItemType == LogicValue::ItemType::Heart)
	{
		if (Heart)
		{
			m_Count = 2;
		}
		else
		{
			m_Count = 1;
		}
	}
	Create();
}

void PickUpItem::Create()
{
	m_RenderBody->SetRenderScale(GetSize()*2);
	switch (m_ItemType)
	{
	case LogicValue::ItemType::Coin:
		m_RenderBody->SetRenderScale(GetSize() * 4);
		m_RenderBody->CreateAnimation(L"Idle", L"PickUp_Coin.bmp", 0, 5, 0.05f);
		m_RenderBody->CreateAnimation(L"Play", L"PickUp_Coin.bmp", 8, 15, 0.05f, false);
		m_RenderBody->CreateAnimation(L"Effect", L"PickUp_Coin.bmp", 16, 23, 0.05f, false);
		m_RenderBody->ChangeAnimation(L"Play");
		break;
	case LogicValue::ItemType::Bomb:
		m_RenderBody->CreateAnimation(L"Idle", L"bombs.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Play", L"bombs.bmp", 0, 0, 0.1f, false);
		m_RenderBody->CreateAnimation(L"Effect", L"bombs.bmp", 0, 0, 0.05f, false);

		m_RenderBody->ChangeAnimation(L"Idle");
		break;
	case LogicValue::ItemType::Heart:
		if (m_Count==1)
		{

			m_RenderBody->CreateAnimation(L"Idle", L"PickUp_heart.bmp", 1, 1, 0.1f);
			m_RenderBody->CreateAnimation(L"Play", L"PickUp_heart.bmp", 1, 1, 0.1f, false);
			m_RenderBody->CreateAnimation(L"Effect", L"PickUp_heart.bmp", 1, 1, 0.05f, false);
		}
		else
		{
			m_RenderBody->CreateAnimation(L"Idle", L"PickUp_heart.bmp", 0, 0, 0.1f);
			m_RenderBody->CreateAnimation(L"Play", L"PickUp_heart.bmp", 0, 0, 0.1f, false);
			m_RenderBody->CreateAnimation(L"Effect", L"PickUp_heart.bmp", 0, 0, 0.05f, false);
		}
		m_RenderBody->ChangeAnimation(L"Play");
		HeartNext();
		break;

	case LogicValue::ItemType::Max:
		EngineDebug::AssertMsg("case LogicValue::PickUp_ItemType::Max:");
		break;
	default:
		break;
	}

}

void PickUpItem::MapCollision()
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

void PickUpItem::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player))
	{
		if (m_Time < 1.f)
		{
			return;
		}

		Player* player=LogicValue::MainPlayer;
		if (!m_bCollision)
		{
			if (m_ItemType == LogicValue::ItemType::Bomb)
			{
				if (player->GetCharacterInfo()->BombAdd())
				{

					EngineSound::Play(L"BombPickUp.mp3", false, 0);

					m_RenderBody->ChangeAnimation(L"Effect");
					m_bCollision = true;
				}
			}
			else if (m_ItemType == LogicValue::ItemType::Coin)
			{
				if (player->GetCharacterInfo()->CoinAdd())
				{
					EngineSound::Play(L"Coinpickup.mp3", false, 0);
					m_RenderBody->ChangeAnimation(L"Effect");
					m_bCollision = true;
				}
			}
			else if (m_ItemType == LogicValue::ItemType::Heart)
			{
				if (player->GetCharacterInfo()->GetHP() < player->GetCharacterInfo()->GetHPMax())
				{
					player->GetCharacterInfo()->HPAdd(m_Count);
					m_bCollision = true;
					EngineSound::Play(L"heartIntake.mp3", false, 0);
				}
			}
			else
			{
				EngineDebug::AssertMsg("else if (m_ItemType == ????????????????");
			}
		}

		//한번 체크했는데 플레이어랑 충돌했어도 못먹었음
		if (!m_bCollision)
		{
			float4 Dir = _This->GetPosition() - _Other->GetPosition();
			m_CharacterInfo->AccelSpeedMove(Dir, 0.8f);
		}

	}

	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 2.f);
	}
}

void PickUpItem::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void PickUpItem::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player))
	{
		if (!m_bCollision)
		{
			float4 Dir = _This->GetPosition() - _Other->GetPosition();
			m_CharacterInfo->AccelSpeedMove(Dir, 0.8f);
		}
	}
	
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::ShopItemObject))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();

		if (_This->GetPosition() == _Other->GetPosition())
		{
			Dir = float4::GetRandomAngleRad();
		}

		m_CharacterInfo->AccelSpeedMove(Dir, 0.8f);
		
	}
}
