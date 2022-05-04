#include "BossUI.h"
#include <EngineRendererBasic.h>
//static
//static func

BossUI::BossUI() :m_BossHPRender(nullptr), m_BossHPLayer(nullptr)
{
}

BossUI::~BossUI()
{
}

void BossUI::Start()
{
	m_BossHPRender = CreateRenderer<EngineRendererBasic>(10);
	m_BossHPRender->TransCut_Setting(L"UI_bosshealthbar.bmp", 1);
	m_BossHPRender->TransNotCenter();
	m_BossHPRender->CamPosOff();
	m_BossHPRender->SetPivotPos({ 350.f, 30.f });

	m_BossHPLayer = CreateRenderer<EngineRendererBasic>(11);
	m_BossHPLayer->TransSetting(L"UI_bosshealthbar.bmp", { 300.f, 64.f });
	m_BossHPLayer->TransNotCenter();
	m_BossHPLayer->CamPosOff();

	m_BossHPLayer->SetCutSize({ 40.f, 64.f });
	m_BossHPLayer->SetRenderScale({ 40.f, 64.f });
	m_BossHPLayer->SetPivotPos({ 350.f, 30.f });
	//ÄÚµùÁß
	Off();
}


void BossUI::Update()
{

}

void BossUI::SetPercentBar(float _Percent)
{
	m_BossHPLayer->SetCutSize({ 300.f * _Percent, 64.f });
	m_BossHPLayer->SetRenderScale({ 300.f * _Percent, 64.f });
}
