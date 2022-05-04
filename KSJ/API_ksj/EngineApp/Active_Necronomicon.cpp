#include "Active_Necronomicon.h"
#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include "PlayScene.h"
#include "RoomInfo.h"
#include "ItemEffect.h"
//static
//static func


Active_Necronomicon::Active_Necronomicon()
{
}

Active_Necronomicon::~Active_Necronomicon()
{
}

void Active_Necronomicon::Start()
{
	ActiveItem::Start();
	m_RenderBody->TransSetting(L"collectibles_thenecronomicon.bmp", { 64.f,64.f });
	m_RenderBody->CamPosOff();
	m_RenderBody->SetPivotPos({ 50,40 });


}

void Active_Necronomicon::Play()
{
	Player* player = LogicValue::MainPlayer;
	float4 mapcount=player->GetMapCount();
	
	RoomInfo* room = LogicValue::MainScene->GetMap(mapcount.ix(), mapcount.iy());
	ItemEffect* effect = GetScene()->CreateActor<ItemEffect>();
	effect->SetRoom(room);
}

int Active_Necronomicon::ItemType()
{
	int temp = static_cast<int>(LogicValue::ItemGroup::Active_Necronomicon);
	return temp;
}
