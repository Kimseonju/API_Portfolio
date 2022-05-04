#include "Item_haloofflies.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>

#include "ProtectionFly.h" //임시
#include "Itemaltar.h"
//static
//static func


Item_haloofflies::Item_haloofflies(): m_Anim(nullptr),
m_Basic(nullptr)
{
}

Item_haloofflies::~Item_haloofflies()
{
}

void Item_haloofflies::Start()
{
	Item::Start();
	m_ItemRenderer->TransSetting(L"collectibles_010_haloofflies.bmp", { 64.f,64.f });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });
	
}

void Item_haloofflies::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	EngineScene* Scene=player->GetScene();
	ProtectionFly* actor = Scene->CreateActor<ProtectionFly>(); //임시로 Fly넣음;
	//현재 아이템 죽으므로 삭제
	m_Itemaltar->SetItem(nullptr);
	//파리를 소환하여 플레이어 주위를 돈다.
	actor->SetParentBase(player);
	player->ProtectionActorAdd(actor);
	if (nullptr != m_Anim)
	{
		m_Anim->Death();
	}
	if (nullptr != m_Basic)
	{
	EngineSound::Play(L"isaac_powerup_spewer.mp3", false, 0);
		m_Basic->Death();
	}
	Death();
}

EngineRendererBasic* Item_haloofflies::PlayerRenderItem()
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
	m_Basic->TransSetting(L"collectibles_010_haloofflies.bmp", { 64.f,64.f });
	m_Basic->SetPivotMove({ 0.f,-45.f });
	m_Basic->SetActor(LogicValue::MainPlayer);
	m_Basic->SetParentBase(LogicValue::MainPlayer);

	return m_Basic;
}
