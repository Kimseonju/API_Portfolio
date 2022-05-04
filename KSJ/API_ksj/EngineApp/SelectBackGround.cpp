#include "SelectBackGround.h"
#include <EngineWindow.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
#include <EngineRendererBasic.h>
// Static Var
// Static Func

// member Var
SelectBackGround::SelectBackGround()
{

}

SelectBackGround::~SelectBackGround()
{

}
// member Func
void SelectBackGround::Start()
{
	{
		//배경화면
		EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(0);
		NewRenderer->TransSetting(L"SelectMenu.bmp", { 960, 540 });
		NewRenderer->SetPivotPos({ 0.0f,0.0f });
	}
}
void SelectBackGround::Update()
{

}