#include "Costume_HolyGrail.h"
#include <EngineRendererAnim.h>
//static
//static func


Costume_HolyGrail::Costume_HolyGrail()
{
}

Costume_HolyGrail::~Costume_HolyGrail()
{
}

void Costume_HolyGrail::Start()
{
	Player_ItemCostume::Start();
	m_RenderHead->SetRenderScale({ 96, 96 });
	m_RenderHead->CreateAnimation(L"DownFire", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightFire", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftFire", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpFire", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);

	m_RenderHead->CreateAnimation(L"DownIdle", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightIdle", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftIdle", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpIdle", L"costume_HolyGrail.bmp", 0, 0, 0.2f, true, false);

	m_RenderHead->ChangeAnimation(L"DownIdle");
	m_RenderHead->SetAlpha(200);
	MovePosition({ 0,-2 });
}

void Costume_HolyGrail::Update()
{
}
