#include "Itemaltar.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include "Player.h"
#include "Item.h"
#include "Item_haloofflies.h"
#include "Item_lunch.h"
#include "Item_momslipstick.h"
#include "Item_thesadonion.h"
#include "Item_Wirecoathanger.h"
#include "Item_HolyGrail.h"
#include "Item_familiar_brotherbobby.h"
#include "Item_familiar_littlechad.h"
#include "Item_familiar_sackofpennies.h"
#include "Item_familiar_sistermaggie.h"
#include "Item_Active_Kamikaze.h"
#include "Item_Active_Necronomicon.h"
#include "Item_mutantspider.h"
#include "Item_Polyphemus.h"
#include "Item_spoonbender.h"
#include "Item_catoninetails.h"
#include <EngineScene.h>
// Static Var
// Static Func

// member Var
Itemaltar::Itemaltar():m_Collision(nullptr), m_Item(nullptr), m_RenderBody(nullptr)
, m_ItemColStart(false)
, m_TempItem(nullptr)
{

}

Itemaltar::~Itemaltar()
{

}
// member Func

void Itemaltar::Start()
{

	{
		m_RenderBody = CreateRenderer<EngineRendererBasic>(500);
		m_RenderBody->TransSetting(L"Itemaltar.bmp", { 64, 64 });
	}
	{
		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::PlayerItem));
		m_Collision->SetPivotPos({ 0.f, 30.f });
		m_Collision->SetScale({ 30.f,20.f });
		m_Collision->AddStartEvent(this, &Itemaltar::StartCol);
		m_Collision->AddStayEvent(this, &Itemaltar::StayCol);
		m_Collision->AddEndEvent(this, &Itemaltar::EndCol);
	}
	CreateItem();
}
void Itemaltar::Update()
{
	if (m_Item)
	{
		m_Item->SetPosition(GetPosition());
	}
	
}

void Itemaltar::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player))
	{

		if (nullptr != m_Item)
		{
			if (!m_ItemColStart)
			{
				ItemInPlayer();
			}
		}
		
	}
}

void Itemaltar::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Itemaltar::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Itemaltar::PlayerFarming()
{
	m_Item->PlayerFarming();
}

void Itemaltar::CreateItem()
{
	LogicValue::ItemGroup ItemNumber= Item::GetItemNumber();
	m_Item=CreateItem(ItemNumber);
}

Item* Itemaltar::CreateItem(LogicValue::ItemGroup _ItemGroup)
{

	Item* item = nullptr;
	switch (_ItemGroup)
	{
	case LogicValue::ItemGroup::haloofflies:
		item = GetScene()->CreateActor<Item_haloofflies>();
		break;
	case LogicValue::ItemGroup::lunch:
		item = GetScene()->CreateActor<Item_lunch>();
		break;
	case LogicValue::ItemGroup::momslipstick:
		item = GetScene()->CreateActor<Item_momslipstick>();
		break;
	case LogicValue::ItemGroup::thesadonion:
		item = GetScene()->CreateActor<Item_thesadonion>();
		break;
	case LogicValue::ItemGroup::Wirecoathanger:
		item = GetScene()->CreateActor<Item_Wirecoathanger>();
		break;
	case LogicValue::ItemGroup::HolyGrail:
		item = GetScene()->CreateActor<Item_HolyGrail>();
		break;
	case LogicValue::ItemGroup::Familiar_brotherbobby:
		item = GetScene()->CreateActor<Item_familiar_brotherbobby>();
		break;
	case LogicValue::ItemGroup::Familiar_littlechad:
		item = GetScene()->CreateActor<Item_familiar_littlechad>();
		break;
	case LogicValue::ItemGroup::Familiar_sackofpennies:
		item = GetScene()->CreateActor<Item_familiar_sackofpennies>();
		break;
	case LogicValue::ItemGroup::Familiar_sistermaggie:
		item = GetScene()->CreateActor<Item_familiar_sistermaggie>();
		break;
	case LogicValue::ItemGroup::Active_Kamikaze:
		item = GetScene()->CreateActor<Item_Active_Kamikaze>();
		break;
	case LogicValue::ItemGroup::Active_Necronomicon:
		item = GetScene()->CreateActor<Item_Active_Necronomicon>();
		break;
	case LogicValue::ItemGroup::Mutantspider:
		item = GetScene()->CreateActor<Item_mutantspider>();
		break;
	case LogicValue::ItemGroup::Polyphemus:
		item = GetScene()->CreateActor<Item_Polyphemus>();
		break;
	case LogicValue::ItemGroup::Spoonbender:
		item = GetScene()->CreateActor<Item_spoonbender>();
		break;

	case LogicValue::ItemGroup::Catoninetails:
		item = GetScene()->CreateActor<Item_catoninetails>();
		break;
	case LogicValue::ItemGroup::MAX:
		EngineDebug::AssertMsg("case LogicValue::ItemGroup::MAX:");
		break;
	default:
		break;
	}
	item->SetPosition(GetPosition());
	item->SetItemaltar(this);
	return item;
}

void Itemaltar::CreateTempItem(LogicValue::ItemGroup _ItemGroup)
{
	m_TempItem = CreateItem(_ItemGroup);
}

void Itemaltar::ChangeTempItem_Item()
{
	if (!m_TempItem)
		EngineDebug::AssertMsg("if(!m_TempItem)");
	m_Item = m_TempItem;
}

void Itemaltar::ItemOffShop()
{
	m_Collision->Off();
}
void Itemaltar::ItemOnShop()
{
	m_Collision->On();
}
void Itemaltar::ItemInPlayer()
{
	Player* player = LogicValue::MainPlayer;
	if (nullptr == player)
	{
		EngineDebug::AssertMsg("if (nullptr == LogicValue::MainPlayer)");
	}
	if (true == player->IsCollectionItem())
	{
		return;
	}

	m_Collision->Off();
	m_ItemColStart = true;
	EngineSound::Play(L"choir.mp3", false, 0);
	m_Item->Off();
	m_Item->PlayerRenderItem();
	player->SetItemfunction(this, &Itemaltar::PlayerFarming);
}

