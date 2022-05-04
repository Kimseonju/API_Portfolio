#include "RoomEditorBackground.h"
#include "EngineRendererBasic.h"
//static
//static func


RoomEditorBackground::RoomEditorBackground()
{
}

RoomEditorBackground::~RoomEditorBackground()
{
}

void RoomEditorBackground::Start()
{
	EngineRendererBasic* Background = CreateRenderer<EngineRendererBasic>(1);
	Background->TransSetting(L"Basement1.bmp", { 960, 540 });
	Background->CamPosOff();
	Background->TransNotCenter();
}

void RoomEditorBackground::Update()
{
}
