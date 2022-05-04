#include "MapCollider.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
#include <EngineWinImage.h>
// Static Var
// Static Func

// member Var
MapCollider::MapCollider()
{

}

MapCollider::~MapCollider()
{

}
// member Func

void MapCollider::Start()
{

}

void MapCollider::Update()
{
	float4 MapSize = EngineWindow::GetSize();

	float4 Pos = GetScene()->GetCamPos();
	Pos.x = Pos.x + MapSize.ihx();
	Pos.y = Pos.y + MapSize.ihy();
	SetPosition(Pos);
}

void MapCollider::DebugRender()
{
	EngineWinImage* m_Image = EngineWindowResMgr::Inst().FindImage(L"MapCollider.bmp");
	m_Image->SetTransColor(RGB(255, 255, 255));
	EngineWindow::GetBackBufferImage().TransparentBltCenter(EngineWindow::GetSize().hfloat4(), { 960, 540 }, *m_Image, 0, { 960, 540 });
}


