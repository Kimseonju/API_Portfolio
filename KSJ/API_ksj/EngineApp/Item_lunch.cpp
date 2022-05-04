#include "Item_lunch.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>

#include "HeartEffect.h"
#include "Itemaltar.h"
//static
//static func


Item_lunch::Item_lunch():
	m_Anim(nullptr),
	m_Basic(nullptr)
{
}

Item_lunch::~Item_lunch()
{
}

void Item_lunch::Start()
{
	Item::Start();
	m_ItemRenderer->TransSetting(L"collectibles_022_lunch.bmp", { 64.f,64.f });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });
}

void Item_lunch::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	//현재 아이템 죽으므로 삭제
	m_Itemaltar->SetItem(nullptr);
	player->GetCharacterInfo()->SetHPMax(player->GetCharacterInfo()->GetHPMax() + 2);
	player->GetCharacterInfo()->SetHP(player->GetCharacterInfo()->GetHP() + 2);
	HeartEffect* effect=player->GetScene()->CreateActor<HeartEffect>();
	effect->SetParentBase(player);
	EngineSound::Play(L"StateUp.mp3", false, 0);
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

EngineRendererBasic* Item_lunch::PlayerRenderItem()
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
	m_Basic->TransSetting(L"collectibles_022_lunch.bmp", { 64.f,64.f });
	m_Basic->SetPivotMove({ 0.f,-45.f });
	m_Basic->SetActor(LogicValue::MainPlayer);
	m_Basic->SetParentBase(LogicValue::MainPlayer);

	return m_Basic;
}