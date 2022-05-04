#include "BombUI.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
#include "Player.h"
//static
//static func


BombUI::BombUI() : m_TenRender(nullptr), m_OneRender(nullptr)
{
}

BombUI::~BombUI()
{
}

void BombUI::Start()
{
	EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
	//´Ù ºóÄ­À¸·Î ÃÊ±âÈ­
	NewRenderer->TransCut_Setting(L"HUD_PickUp.bmp", 3);
	NewRenderer->SetPivotPos(float4(30.f, 125.f));
	NewRenderer->CamPosOff();


	m_OneRender = CreateRenderer<EngineRendererBasic>(1);
	m_OneRender->TransCut_Setting(L"NumberFont.bmp", 0);
	m_OneRender->SetPivotPos(float4(63.f, 127.f));
	m_OneRender->CamPosOff();

	m_TenRender = CreateRenderer<EngineRendererBasic>(1);
	m_TenRender->TransCut_Setting(L"NumberFont.bmp", 0);
	m_TenRender->SetPivotPos(float4(50.f, 127.f));
	m_TenRender->CamPosOff();

}

void BombUI::Update()
{
	int Bomb = 0;
	if (LogicValue::MainPlayer != nullptr)
	{
		Bomb = LogicValue::MainPlayer->GetCharacterInfo()->GetBomb();
	}
	m_TenRender->TransCut_Setting(L"NumberFont.bmp", Bomb / 10);
	m_OneRender->TransCut_Setting(L"NumberFont.bmp", Bomb % 10);
}
