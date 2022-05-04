#include "TitleButton.h"
#include <EngineWindow.h>

// Static Var
// Static Func

// member Var
TitleButton::TitleButton()
{

}

TitleButton::~TitleButton()
{

}
// member Func

void TitleButton::Update()
{
	float4 Pos = GetPosition();
	Pos.x += 0.1f;

	SetPosition(Pos);

	Rectangle(
		EngineWindow::GetBackBufferDC(),
		GetPosition().ix() - m_Scale.ihx(), //한가운데로 그려진다
		GetPosition().iy() - m_Scale.ihy(),
		GetPosition().ix() + m_Scale.ihx(),
		GetPosition().iy() + m_Scale.ihy());
}