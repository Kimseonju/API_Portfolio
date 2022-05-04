#include "PlayFadeOut.h"
#include <EngineRendererBasic.h>
#include <EngineTimer.h>
#include "Core.h"
#include "LogicValue.h"
#include "Player.h"
//static
//static func

PlayFadeOut::PlayFadeOut() : m_Render(nullptr), m_RenderIcon(nullptr), Alpha(0)
{

}

PlayFadeOut::~PlayFadeOut()
{

}


void PlayFadeOut::Start()
{
	{
		m_Render = CreateRenderer<EngineRendererBasic>(10005);
		m_Render->CamPosOff();
		m_Render->TransSetting(L"fadein.bmp", { 960, 540 });
		m_Render->SetPivotPos({ 960 * 0.5f, 540 * 0.5f });
		m_RenderIcon = CreateRenderer<EngineRendererBasic>(10005);
		m_RenderIcon->CamPosOff();
		m_RenderIcon->TransSetting(L"loadimages.bmp", { 224, 276 });
		m_RenderIcon->SetPivotPos({ 960 * 0.5f, 540 * 0.5f });
	}

	FadeOutTimer.CreateTimeEvent(3.0f, this, &PlayFadeOut::FadeOutEnd, &PlayFadeOut::FadeOutStart, &PlayFadeOut::FadeOut);

}


void PlayFadeOut::Update()
{
	FadeOutTimer.Update();
}

void PlayFadeOut::FadeOutStart()
{
	Alpha = 2.55f;
}

void PlayFadeOut::FadeOut()
{
	Alpha -= EngineTimer::MainTimer.GetFDeltaTime();
	int iAlpha = 0;
	if (0.0f >= Alpha)
	{
		Alpha = 0.0f;
		iAlpha = 0;
	}
	else {
		iAlpha = static_cast<int>((Alpha * 100.0f));
	}
	m_Render->SetAlpha(iAlpha);
	m_RenderIcon->SetAlpha(iAlpha);
}

void PlayFadeOut::FadeOutEnd()
{
	EngineSound::Play(L"GameBGM.mp3", true, 5);
	EngineSound::Volume(L"GameBGM.mp3", 0.7f);
	m_Render->SetAlpha(0);
	m_RenderIcon->SetAlpha(0);
	Death();
}
