#include "Costume_HolyGrail_Body.h"
#include <EngineRendererAnim.h>
//static
//static func


Costume_HolyGrail_Body::Costume_HolyGrail_Body()
{
}

Costume_HolyGrail_Body::~Costume_HolyGrail_Body()
{
}

void Costume_HolyGrail_Body::Start()
{
	Player_ItemCostume::Start();
	m_RenderHead->SetRenderScale({ 128, 114 });


	m_RenderHead->CreateAnimation(L"DownFire", L"costume_HolyGrail_Body.bmp", 0, 6, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightFire", L"costume_HolyGrail_Body.bmp", 14, 20, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftFire", L"costume_HolyGrail_Body.bmp", 21, 27, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpFire", L"costume_HolyGrail_Body.bmp", 7, 13, 0.2f, true, false);

	m_RenderHead->CreateAnimation(L"DownIdle", L"costume_HolyGrail_Body.bmp", 0, 6, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightIdle", L"costume_HolyGrail_Body.bmp", 14, 20, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftIdle", L"costume_HolyGrail_Body.bmp", 21, 27, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpIdle", L"costume_HolyGrail_Body.bmp", 7, 13, 0.2f, true, false);
	
	m_RenderHead->ChangeAnimation(L"DownIdle");
	MovePosition({ 0,-2 });
}

void Costume_HolyGrail_Body::Update()
{
}

void Costume_HolyGrail_Body::SetAnimFrameTimer(float _Time)
{
	m_RenderHead->SetAllAnimTimer(0.2f);
}
