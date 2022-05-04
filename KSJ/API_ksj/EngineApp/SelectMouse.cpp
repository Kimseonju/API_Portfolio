#include "SelectMouse.h"
#include <EngineWindow.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
#include <EngineRendererBasic.h>
// Static Var
// Static Func

// member Var
SelectMouse::SelectMouse()
{

}

SelectMouse::~SelectMouse()
{

}
// member Func
void SelectMouse::Start()
{
	{
		EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(0);
		NewRenderer->TransSetting(L"SelectMouse.bmp", { 24, 30 });
		NewRenderer->SetPivotPos({ 0.0f,0.0f });
	}
}
void SelectMouse::Update()
{

}