#include "Title_Start.h"
#include <EngineWindow.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
#include <EngineRendererBasic.h>
// Static Var
// Static Func

// member Var
Title_Start::Title_Start(): RenderBody(nullptr)
{

}

Title_Start::~Title_Start()
{

}
// member Func
void Title_Start::Start()
{

	EngineWindowResMgr::Inst().FindImage(L"titleStart.bmp")->SetTransColor(RGB(255, 255, 255));

	RenderBody = CreateRenderer<EngineRendererAnim>(1);
	RenderBody->SetRenderScale({ 320, 324 });
	RenderBody->CreateAnimation(L"Idle", L"titleStart.bmp", 0, 1,0.3f);
	RenderBody->SetPivotPos({ 0, 50 });
	RenderBody->ChangeAnimation(L"Idle");
}
void Title_Start::Update()
{

}