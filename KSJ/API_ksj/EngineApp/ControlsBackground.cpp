#include "ControlsBackground.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
//static
//static func


ControlsBackground::ControlsBackground() :NewRenderer(nullptr)
{
}

ControlsBackground::~ControlsBackground()
{
}

void ControlsBackground::Init(const float4& m_MapCount)
{
	float4 MapSize = EngineWindow::GetSize();
	SetPosition({ (MapSize.ix() * (m_MapCount.ix())) + MapSize.ihx(), (MapSize.iy() * (m_MapCount.iy())) + MapSize.ihy() });
	
	NewRenderer->TransCut_Setting(L"controls.bmp", 0);
	
}

void ControlsBackground::Start()
{
	NewRenderer = CreateRenderer<EngineRendererBasic>(0);
}

void ControlsBackground::Update()
{

}
