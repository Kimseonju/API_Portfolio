#include "Item_familiar_littlechad.h"


#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineDebug.h>
#include "CCharacterInfo.h"
#include <EngineScene.h>

#include "ProtectionFly.h" //�ӽ�
#include "Familiar_littlechad.h"
#include "Itemaltar.h"
//static
//static func


Item_familiar_littlechad::Item_familiar_littlechad() : m_Anim(nullptr),
m_Basic(nullptr)
{
}

Item_familiar_littlechad::~Item_familiar_littlechad()
{
}

void Item_familiar_littlechad::Start()
{
	Item::Start();
	m_ItemRenderer->TransCut_Setting(L"familiar_littlechad.bmp", 0);
	m_ItemRenderer->SetRenderScale({ 64,64 });
	m_ItemRenderer->SetPivotPos({ 0.f, -40.f });

}

void Item_familiar_littlechad::PlayerFarming()
{
	if (nullptr == LogicValue::MainPlayer)
		EngineDebug::AssertMsg("if(nullptr==LogicValue::MainPlayer)");

	Player* player = LogicValue::MainPlayer;
	EngineScene* Scene = player->GetScene();

	//���� ������ �����Ƿ� ����
	m_Itemaltar->SetItem(nullptr);

	//�йи�� �����´�.
	Familiar_littlechad* actor = Scene->CreateActor<Familiar_littlechad>();
	actor->SetPosition(player->GetPosition());
	//Ÿ�ٰ� �÷��̾ �־��ش�.
	player->FamiliarPush_TargetSetting(actor);

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

EngineRendererBasic* Item_familiar_littlechad::PlayerRenderItem()
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
	m_Basic->TransCut_Setting(L"familiar_littlechad.bmp", 0);
	m_Basic->SetRenderScale({ 64,64 });
	m_Basic->SetPivotMove({ 0.f,-45.f });
	m_Basic->SetActor(LogicValue::MainPlayer);
	m_Basic->SetParentBase(LogicValue::MainPlayer);

	return m_Basic;
}
