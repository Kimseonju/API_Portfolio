#include "Item_HolyGrail.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>

#include "ProtectionFly.h" //임시
#include "Costume_HolyGrail.h"
#include "Costume_HolyGrail_Body.h"
#include "Itemaltar.h"
//static
//static func


Item_HolyGrail::Item_HolyGrail() : m_Anim(nullptr),
m_Basic(nullptr)
{
}

Item_HolyGrail::~Item_HolyGrail()
{
}

void Item_HolyGrail::Start()
{
	Item::Start();
	m_ItemRenderer->TransSetting(L"collectibles_holygrail.bmp", { 64.f,64.f });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });

}

void Item_HolyGrail::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	EngineScene* Scene = player->GetScene();

	//현재 아이템 죽으므로 삭제
	m_Itemaltar->SetItem(nullptr);

	{
		Costume_HolyGrail* ItemCostume = player->GetScene()->CreateActor<Costume_HolyGrail>();
		ItemCostume->SetParentBase(player);
		player->ItemCostume_Push(ItemCostume);
	}
	{

		Costume_HolyGrail_Body* ItemCostume = player->GetScene()->CreateActor<Costume_HolyGrail_Body>();
		ItemCostume->SetParentBase(player);
		player->ItemCostume_Push(ItemCostume);
	}
	EngineSound::Play(L"isaac_powerup_spewer.mp3", false, 0);

	player->SetFly(true);
	player->GetCharacterInfo()->SetMaxSpeed(player->GetCharacterInfo()->GetMaxSpeed() + 100);
	//플레이어는 날고있으므로 Order는 끝판왕임
	player->SetRenderOrderFly();
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

EngineRendererBasic* Item_HolyGrail::PlayerRenderItem()
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
	m_Basic->TransSetting(L"collectibles_holygrail.bmp", { 64.f,64.f });
	m_Basic->SetPivotMove({ 0.f,-45.f });
	m_Basic->SetActor(LogicValue::MainPlayer);
	m_Basic->SetParentBase(LogicValue::MainPlayer);

	return m_Basic;
}
