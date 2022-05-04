#include "SelectFadeIn.h"
#include <EngineRendererBasic.h>
#include <EngineTimer.h>
#include "Core.h"
//static
//static func

SelectFadeIn::SelectFadeIn() : m_Render(nullptr), m_RenderIcon(nullptr), Alpha(0)
{

}

SelectFadeIn::~SelectFadeIn()
{

}


void SelectFadeIn::Start()
{
	{
		m_Render = CreateRenderer<EngineRendererBasic>(5555);
		m_Render->CamPosOff();
		m_Render->TransSetting(L"fadein.bmp", { 960, 540 });
		m_Render->SetPivotPos({ 960 * 0.5f, 540 * 0.5f });
		m_RenderIcon = CreateRenderer<EngineRendererBasic>(5555);
		m_RenderIcon->CamPosOff();
		m_RenderIcon->TransSetting(L"loadimages.bmp", { 224, 276 });
		m_RenderIcon->SetPivotPos({ 960 * 0.5f, 540 * 0.5f });
	}

	FadeOutTimer.CreateTimeEvent(3.0f, this, &SelectFadeIn::FadeOutEnd, &SelectFadeIn::FadeOutStart, &SelectFadeIn::FadeOut);

	m_Render->SetAlpha(0);
	m_RenderIcon->SetAlpha(0);
}


void SelectFadeIn::Update()
{
	FadeOutTimer.Update();
}


void SelectFadeIn::FadeOutStart()
{
	Alpha = 0.0f;
}

void SelectFadeIn::FadeOut()
{
	Alpha += EngineTimer::MainTimer.GetFDeltaTime();
	int iAlpha = 0;
	if (2.55 <= Alpha)
	{
		Alpha = 2.55f;
		iAlpha = 255;
	}
	else {
		iAlpha = static_cast<int>((Alpha * 100.0f));
	}
	m_Render->SetAlpha(iAlpha);
	m_RenderIcon->SetAlpha(iAlpha);
}

void SelectFadeIn::FadeOutEnd()
{
	m_Render->SetAlpha(255);
	m_RenderIcon->SetAlpha(255);
	Core::SceneManager.ChangeScene(L"PlayScene");
}
