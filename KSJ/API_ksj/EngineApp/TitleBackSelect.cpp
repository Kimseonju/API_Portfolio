#include "TitleBackSelect.h"
#include <EngineWindow.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
#include <EngineRendererBasic.h>
// Static Var
// Static Func

// member Var
TitleBackSelect::TitleBackSelect()
	:m_Select(false)
	, m_CamMove(false)
	, m_CamStartPos(float4::ZERO)
	,m_CamEndPos(float4::ZERO)
	, m_CamTime(0.f)
	, m_RenderBody(nullptr)
{

}

TitleBackSelect::~TitleBackSelect()
{

}
// member Func
void TitleBackSelect::Start()
{
	{
		//배경화면
		m_RenderBody = CreateRenderer<EngineRendererBasic>(0);
		m_RenderBody->TransSetting(L"TitleBackSelect.bmp", { 960, 540 });
		m_RenderBody->CamPosOff();
		float4 Pos = EngineWindow::GetSize().hfloat4();
		Pos.y += 200;
		m_RenderBody->SetPivotPos( Pos);
	}
}
void TitleBackSelect::Update()
{
	MapMove();
}
void TitleBackSelect::MapMove()
{

	if (true == m_CamMove)
	{
		m_CamTime += EngineTimer::FDeltaTime(3);
		float4 CurPos = float4::Lerp2DMax(m_CamStartPos, m_CamEndPos, m_CamTime);
		m_RenderBody->SetPivotPos(CurPos);
		if (1.0F <= m_CamTime)
		{
			m_CamMove = false;
		}
	}
}

void TitleBackSelect::MoveStart(bool _Select)
{
	m_CamTime = 0.f;
	m_Select = _Select;
	m_CamMove = true;
	float4 Pos = EngineWindow::GetSize().hfloat4();
	if (m_Select)
	{
		m_CamStartPos = float4{ Pos.x,Pos.y+ 200 };
		m_CamEndPos = Pos;
	}
	else
	{

		m_CamStartPos = Pos;
		m_CamEndPos = float4{ Pos.x,Pos.y + 200 };
	}
}
