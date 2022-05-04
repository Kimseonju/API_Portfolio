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

	//���� ������ �����Ƿ� ����
	m_Itemaltar->SetItem(nullptr);
	//���� �浹 Ű��
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

	//���� ���������ִٸ� ��ü�ؾ���
	Player* player = LogicValue::MainPlayer;
	//��Ƽ�� ������ ����
	ActiveItem* PlayerActiveItem = player->GetActiveItem();
	if (PlayerActiveItem)
	{
		PlayerActiveItem->Off();
		int playerItemType = PlayerActiveItem->ItemType();
		LogicValue::ItemGroup itemgroup = (LogicValue::ItemGroup)playerItemType;

		m_Itemaltar->CreateTempItem(itemgroup);
		m_ItemOn = true;
	}

	//����Ű��
	return m_Basic;
}