#include "ShopItem.h"
#include <EngineRendererBasic.h>
#include <EngineCollision.h>
#include "Itemaltar.h"
#include "Player.h"
//static
//static func

LogicValue::ItemGroup ShopItem::Item= LogicValue::ItemGroup::MAX;
ShopItem::ShopItem() :
	m_RenderBody(nullptr)
	, m_Collision(nullptr)
	, m_CoinNumber10(nullptr)
	, m_CoinNumber1(nullptr)
	, m_Item(nullptr)
	, m_ItemType(LogicValue::ItemType::Max)
	, m_Count(1)
	, m_Price(0)
	, m_itemTimerMax(1.f)
	, m_itemTimer(0.f)
	, m_Costume(false)
{
}

ShopItem::~ShopItem()
{
}

void ShopItem::Start()
{
	SetClassType(L"ShopItem");

	
	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::ShopItemObject));
	m_Collision->AddStartEvent(this, &ShopItem::StartCol);
	m_Collision->AddStayEvent(this, &ShopItem::StayCol);
	m_Collision->AddEndEvent(this, &ShopItem::EndCol);


	//_RenderBody->SetRenderScale({ 64, 64 });
	SetSize({ 24.f,24.f });
	m_Collision->SetScale({ GetSize() });
	m_CoinNumber1 = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::UI));
	m_CoinNumber1->TransCut_Setting(L"NumberFont.bmp", 0);
	m_CoinNumber1->SetPivotPos(float4(3.f, 50.f));

	m_CoinNumber10 = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::UI));
	m_CoinNumber10->TransCut_Setting(L"NumberFont.bmp", 0);
	m_CoinNumber10->SetPivotPos(float4(-10.f, 50.f));

}

void ShopItem::Update()
{
	m_itemTimer += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_Costume)
	{
		if (m_Item == nullptr)
		{
			m_Item = GetScene()->CreateActor<Itemaltar>();
			m_Item->ItemOffShop();
			//위치는 메인이 알아서 잡아줌 메인것만 끌고오면댐
			m_Item->SetParentBase(this);
		}
	}
}

void ShopItem::Init(LogicValue::ItemType _ItemType)
{
	m_RenderBody = CreateRenderer<EngineRendererBasic>(6);

	switch (_ItemType)
	{
	case LogicValue::ItemType::Coin:
		EngineDebug::AssertMsg("case LogicValue::ItemType::Coin");
		break;
	case LogicValue::ItemType::Bomb:

		m_RenderBody->TransCut_Setting(L"bombs.bmp", 0);
		m_Price = 5;
		break;
	case LogicValue::ItemType::Heart:
		m_RenderBody->TransCut_Setting(L"PickUp_heart.bmp", 0);
		m_Count = 2;
		m_Price = 5;
		break;

	case LogicValue::ItemType::Max:
		EngineDebug::AssertMsg("case LogicValue::PickUp_ItemType::Max:");
		break;
	default:
		EngineDebug::AssertMsg("case LogicValue::PickUp_ItemType::Max:");
		break;
	}
	m_ItemType = _ItemType;

	SetCoinImage();
}

void ShopItem::Init()
{
	//아이템 넣기
	//아이템액터 가져오기?
	m_Costume = true;
	m_Price = 15;
	m_Item=GetScene()->CreateActor<Itemaltar>();
	m_Item->ItemOffShop();
	//위치는 메인이 알아서 잡아줌 메인것만 끌고오면댐
	m_Item->SetParentBase(this);
	SetCoinImage();
}
void ShopItem::PlayerFarming()
{
	
	//아이템용
}

void ShopItem::SetCoinImage()
{
	if (m_Price / 10 == 0)
	{
		m_CoinNumber10->Off();
	}
	else
	{
		m_CoinNumber10->TransCut_Setting(L"NumberFont.bmp", m_Price / 10);
	}
	m_CoinNumber1->TransCut_Setting(L"NumberFont.bmp", m_Price % 10);
}


void ShopItem::StartCol(EngineCollision* _This, EngineCollision* _Other)
{

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player) )
	{
		if (m_itemTimer < m_itemTimerMax)
		{
			return;
		}
		m_itemTimer = 0.f;

		Player* player = LogicValue::MainPlayer;

		int coin=player->GetCharacterInfo()->GetCoin();
		//돈없음
		if (coin < m_Price)
		{
			return;
		}
			
		
		if (m_Item)
		{
			//알아서 처리해주겟찡
			if (true == player->IsCollectionItem())
			{
				return;
			}
			m_Item->ItemInPlayer();
			//m_Item->ItemInShop();
			m_Item = nullptr;
		}
		else
		{
			if (m_ItemType == LogicValue::ItemType::Bomb)
			{
				player->GetCharacterInfo()->BombAdd();
				EngineSound::Play(L"BombPickUp.mp3", false, 0);
			}
			else if(m_ItemType == LogicValue::ItemType::Heart)
			{
				if (player->GetCharacterInfo()->GetHP() < player->GetCharacterInfo()->GetHPMax())
				{
					player->GetCharacterInfo()->HPAdd(m_Count);
					EngineSound::Play(L"heartIntake.mp3", false, 0);
				}
				else
				{
					return;
				}
			}
			else
			{
				EngineDebug::AssertMsg("else if(m_ItemType == ????????");
			}
		}
		player->GetCharacterInfo()->CoinSub(m_Price);
	}
	
}

void ShopItem::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void ShopItem::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}


