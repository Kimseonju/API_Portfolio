#include "Item_catoninetails.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>
#include "Costume_catoninetails.h"
#include "Itemaltar.h"
//static
//static func


Item_catoninetails::Item_catoninetails() :
	m_Anim(nullptr),
	m_Basic(nullptr)
{
}

Item_catoninetails::~Item_catoninetails()
{
}

void Item_catoninetails::Start()
{
	Item::Start();
	m_ItemRenderer->TransSetting(L"collectibles_165_catoninetails.bmp", { 64.f,64.f });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });
}

void Item_catoninetails::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	player->GetCharacterInfo()->SetShotSpeed(player->GetCharacterInfo()->GetShotSpeed() +2.f);
	//현재 아이템 죽으므로 삭제
	m_Itemaltar->SetItem(nullptr);
	EngineSound::Play(L"isaac_powerup_spewer.mp3", false, 0);

	Costume_catoninetails* ItemCostume = player->GetScene()->CreateActor<Costume_catoninetails>();
	ItemCostume->SetParentBase(player);
	player->ItemCostume_Push(ItemCostume);

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

EngineRendererBasic* Item_catoninetails::PlayerRenderItem()
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
	m_Basic->TransSetting(L"collectibles_165_catoninetails.bmp", { 64.f,64.f });
	m_Basic->SetPivotMove({ 0.f,-45.f });
	m_Basic->SetActor(LogicValue::MainPlayer);
	m_Basic->SetParentBase(LogicValue::MainPlayer);

	return m_Basic;
}