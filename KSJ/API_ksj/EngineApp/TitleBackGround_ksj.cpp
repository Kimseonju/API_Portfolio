#include "TitleBackGround_ksj.h"
#include <EngineWindow.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
#include <EngineRendererBasic.h>
// Static Var
// Static Func

// member Var
TitleBackGround_ksj::TitleBackGround_ksj()
{

}

TitleBackGround_ksj::~TitleBackGround_ksj()
{

}
// member Func
void TitleBackGround_ksj::Start()
{
	{
		//배경화면
		EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(0);
		NewRenderer->TransSetting(L"Title.bmp", { 960, 540 });
		NewRenderer->SetPivotPos({ 0.0f,0.0f });
	}
}
void TitleBackGround_ksj::Update()
{
}

void TitleBackGround_ksj::DebugRender()
{
}
