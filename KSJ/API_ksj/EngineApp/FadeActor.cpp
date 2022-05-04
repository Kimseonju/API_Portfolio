#include "FadeActor.h"
#include <EngineRendererBasic.h>
#include <EngineTimer.h>

FadeActor::FadeActor() : m_Render(nullptr), Alpha(0)
{

}

FadeActor::~FadeActor()
{

}


void FadeActor::Start()
{
	{
		m_Render = CreateRenderer<EngineRendererBasic>(5555);
		m_Render->CamPosOff();

		m_Render->TransSetting(L"fadein.bmp", { 960, 540 });
		m_Render->SetPivotPos({ 960 * 0.5f, 540 * 0.5f });
	}

	FadeOutTimer.CreateTimeEvent(3.0f, this, &FadeActor::FadeOutEnd, &FadeActor::FadeOutStart, &FadeActor::FadeOut);

}


void FadeActor::Update()
{
	FadeOutTimer.Update();
}

void FadeActor::FadeInStart()
{
	Alpha = 0.0f;
}

void FadeActor::FadeIn()
{
	Alpha += EngineTimer::MainTimer.GetFDeltaTime();
	int iAlpha = 0;
	if (2.55f <= Alpha)
	{
		Alpha = 2.55f;
		iAlpha = 255;
	}
	else {
		iAlpha = static_cast<int>((Alpha * 100.0f));
	}
	m_Render->SetAlpha(iAlpha);
}

void FadeActor::FadeInEnd()
{
	m_Render->SetAlpha(255);
}

void FadeActor::FadeOutStart()
{
	Alpha = 2.55f;
}

void FadeActor::FadeOut()
{
	Alpha -= EngineTimer::MainTimer.GetFDeltaTime() / 3;
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
}

void FadeActor::FadeOutEnd()
{
	m_Render->SetAlpha(0);
}
