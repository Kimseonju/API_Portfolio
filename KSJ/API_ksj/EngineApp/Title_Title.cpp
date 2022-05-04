#include "Title_Title.h"
#include <EngineWindow.h>
#include <EngineWindowResMgr.h>
#include <EngineTimer.h>
#include <EngineRendererBasic.h>
// Static Var
// Static Func

// member Var
Title_Title::Title_Title():
	RotRender(nullptr),
	m_LeftRight(false),
	m_Angle(-1.3f)
	, onePlay(false)
{

}

Title_Title::~Title_Title()
{

}
// member Func
void Title_Title::Start()
{
	{
		//배경화면
		//EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
		//NewRenderer->TransSetting(L"title_title.bmp", { 960, 208 });
		//NewRenderer->SetPivotPos({ 0.0f,-150.0f });
	}

	RotRender = CreateRenderer<EngineRendererBasic>(2);
	RotRender->RotImageSetting(L"title_title.bmp", L"title_titlemask.bmp", { 960, 208 });
	RotRender->SetPivotPos({ 0.0f,-150.0f });
	float4 Dir = float4::AngleToDir2DDeg(m_Angle);

	RotRender->SetAngle(m_Angle);
}
void Title_Title::Update()
{
	//첫로딩시 타임이 밀려서 회전이 길게됨 첫회전생략;
	if (!onePlay)
	{
		onePlay = true;
		return;
	}

	if (m_Angle <= -1.5f)
	{
		m_LeftRight = true;
	}
	else if(m_Angle>=2.0f)
	{
		m_LeftRight = false;
	}

	if (m_LeftRight)
	{
		m_Angle += EngineTimer::FDeltaTime(3.0f);
		float4 Dir = float4::AngleToDir2DDeg(m_Angle);

		RotRender->SetAngle(m_Angle);
	}
	else
	{

		m_Angle -= EngineTimer::FDeltaTime(3.0f);
		float4 Dir = float4::AngleToDir2DDeg(m_Angle);

		RotRender->SetAngle(m_Angle);
	}
}