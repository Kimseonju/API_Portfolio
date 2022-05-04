#include "Item_Active_Kamikaze.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>
#include "Costume_SadOnion.h"
#include "Active_Kamikaze.h"
#include "Itemaltar.h"
//static
//static func


Item_Active_Kamikaze::Item_Active_Kamikaze()
	:m_Anim(nullptr)
	, m_Basic(nullptr)
	, m_ItemOn(false)
{
}

Item_Active_Kamikaze::~Item_Active_Kamikaze()
{
}

void Item_Active_Kamikaze::Start()
{
	Item::Start();
	m_ItemRenderer->TransSetting(L"collectibles_kamikaze.bmp", { 64.f,64.f });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });
}

void Item_Active_Kamikaze::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	ActiveItem* activeitem = GetScene()->CreateActor<Active_Kamikaze>();
	player->SetActiveItem(activeitem);

	//현재 아이템 죽으므로 삭제
	m_Itemaltar->SetItem(nullptr);
	//이제 충돌 키기
	if (m_ItemOn)
	{
		m_Itemaltar->ChangeTempItem_Item();
		m_Itemaltar->ItemOnShop();
		m_ItemOn = false;
		m_Itemaltar->SetItemColStart(false);
	}

	if (nullptr != m_Anim)
	{
		m_Anim->Death();
	}
	if (nullptr != m_Basic)
	{
		m_Basic->Death();
	}
	Death();
}
EngineRendererBasic* Item_Active_Kamikaze::PlayerRenderItem()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if (nullptr == LogicValue::MainPlayer)");

	m_Anim = CreateRenderer<EngineRendererAnim>(static_cast<int>(LogicValue::RenderGroup::Item));
	m_Anim->CreateAnimation(L"Play", L"ItemEffect.bmp", 0, 5);
	m_Anim->SetRenderScale({ 64, 64 });
	m_Anim->SetPivotMove({ 0.f,-40.f });
	m_Anim->SetActor(LogicValue::MainPlayer);
	m_Anim->SetParentBase(LogicValue::MainPlayer);
	m_Anim->ChangeAnimation(L"Play");

	m_Basic = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Item));
	m_Basic->TransSetting(L"collectibles_kamikaze.bmp", { 64.f,64.f });
	m_Basic->SetPivotMove({ 0.f,-45.f });
	m_Basic->SetActor(LogicValue::MainPlayer);
	m_Basic->SetParentBase(LogicValue::MainPlayer);

	//만약 아이템이있다면 교체해야함
	Player* player = LogicValue::MainPlayer;
	//액티브 아이템 변경
	ActiveItem* PlayerActiveItem = player->GetActiveItem();
	if (PlayerActiveItem)
	{
		PlayerActiveItem->Off();
		int playerItemType = PlayerActiveItem->ItemType();
		LogicValue::ItemGroup itemgroup = (LogicValue::ItemGroup)playerItemType;

		m_Itemaltar->CreateTempItem(itemgroup);
		m_ItemOn = true;
	}

	//렌더키기

	return m_Basic;
}