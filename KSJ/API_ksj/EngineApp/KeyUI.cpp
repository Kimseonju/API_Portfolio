#include "KeyUI.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
#include "Player.h"
//static
//static func


KeyUI::KeyUI()
: m_TenRender(nullptr),
m_OneRender(nullptr)
{
}

KeyUI::~KeyUI()
{
}

void KeyUI::Start()
{
	EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
	//´Ù ºóÄ­À¸·Î ÃÊ±âÈ­
	NewRenderer->TransCut_Setting(L"HUD_PickUp.bmp", 1);
	NewRenderer->SetPivotPos(float4(30.f, 150.f));
	NewRenderer->CamPosOff();


	m_OneRender = CreateRenderer<EngineRendererBasic>(1);
	m_OneRender->TransCut_Setting(L"NumberFont.bmp", 0);
	m_OneRender->SetPivotPos(float4(63.f, 152.f));
	m_OneRender->CamPosOff();

	m_TenRender = CreateRenderer<EngineRendererBasic>(1);
	m_TenRender->TransCut_Setting(L"NumberFont.bmp", 0);
	m_TenRender->SetPivotPos(float4(50.f, 152.f));
	m_TenRender->CamPosOff();

}

void KeyUI::Update()
{
	int Key = 0;
	if (LogicValue::MainPlayer != nullptr)
	{
		Key = LogicValue::MainPlayer->GetCharacterInfo()->GetKey();
	}
	m_TenRender->TransCut_Setting(L"NumberFont.bmp", Key / 10);
	m_OneRender->TransCut_Setting(L"NumberFont.bmp", Key % 10);
}
