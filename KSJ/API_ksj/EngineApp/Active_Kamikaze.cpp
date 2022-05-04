#include "Active_Kamikaze.h"
#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include "Player.h"
#include "PlayScene.h"
#include "RoomInfo.h"
#include "BombEffect.h"
//static
//static func


Active_Kamikaze::Active_Kamikaze()
{
}

Active_Kamikaze::~Active_Kamikaze()
{
}

void Active_Kamikaze::Start()
{
	ActiveItem::Start();
	m_RenderBody->TransSetting(L"collectibles_kamikaze.bmp", { 64.f,64.f });
	m_RenderBody->CamPosOff();
	m_RenderBody->SetPivotPos({ 50,40 });
}

void Active_Kamikaze::Play()
{
	Player* player = LogicValue::MainPlayer;
	BombEffect* bombeffect = GetScene()->CreateActor<BombEffect>();
	
	float4 pos = player->GetPosition();
	pos.y += 30.f;
	bombeffect->SetPosition(pos);
}

int Active_Kamikaze::ItemType()
{
	int temp = static_cast<int>(LogicValue::ItemGroup::Active_Kamikaze);
	return temp;
}
