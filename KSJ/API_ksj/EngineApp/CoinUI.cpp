#include "CoinUI.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
#include "Player.h"
#include "CCharacterInfo.h"
//static
//static func

CoinUI::CoinUI() : m_TenRender(nullptr), m_OneRender(nullptr)
{
}

CoinUI::~CoinUI()
{
}

void CoinUI::Start()
{
	EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
	//´Ù ºóÄ­À¸·Î ÃÊ±âÈ­
	NewRenderer->TransCut_Setting(L"HUD_PickUp.bmp", 0);
	NewRenderer->SetPivotPos(float4(30.f, 100.f));
	NewRenderer->CamPosOff();

	m_OneRender = CreateRenderer<EngineRendererBasic>(1);
	m_OneRender->TransCut_Setting(L"NumberFont.bmp", 0);
	m_OneRender->SetPivotPos(float4(63.f, 102.f));
	m_OneRender->CamPosOff();

	m_TenRender = CreateRenderer<EngineRendererBasic>(1);
	m_TenRender->TransCut_Setting(L"NumberFont.bmp", 0);
	m_TenRender->SetPivotPos(float4(50.f, 102.f));





















































































	m_TenRender->CamPosOff();
}

void CoinUI::Update()
{
	int Coin = 0;
	if (LogicValue::MainPlayer != nullptr)
	{
		Coin = LogicValue::MainPlayer->GetCharacterInfo()->GetCoin();
	}
	m_TenRender->TransCut_Setting(L"NumberFont.bmp", Coin / 10);
	m_OneRender->TransCut_Setting(L"NumberFont.bmp", Coin % 10);
}
