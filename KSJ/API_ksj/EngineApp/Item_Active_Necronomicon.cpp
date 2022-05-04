#include "Item_Active_Necronomicon.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>
#include "Costume_SadOnion.h"
#include "ActiveItem.h"
#include "Itemaltar.h"
#include "Active_Necronomicon.h"
//static
//static func


Item_Active_Necronomicon::Item_Active_Necronomicon()
	:m_Anim(nullptr)
	, m_Basic(nullptr)
	, m_ItemOn(false)
{
}

Item_Active_Necronomicon::~Item_Active_Necronomicon()
{
}

void Item_Active_Necronomicon::Start()
{
	Item::Start();
	m_ItemRenderer->TransSetting(L"collectibles_thenecronomicon.bmp", { 64.f,64.f });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });
}

void Item_Active_Necronomicon::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	ActiveItem* activeitem = GetScene()->CreateActor<Active_Necronomicon>();
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
EngineRendererBasic* Item_Active_Necronomicon::PlayerRenderItem()
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
	m_Basic->TransSetting(L"collectibles_thenecronomicon.bmp", { 64.f,64.f });
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