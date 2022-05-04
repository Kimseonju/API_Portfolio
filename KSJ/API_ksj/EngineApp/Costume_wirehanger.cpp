#include "Costume_wirehanger.h"
#include <EngineRendererAnim.h>
//static
//static func


Costume_wirehanger::Costume_wirehanger()
{
}

Costume_wirehanger::~Costume_wirehanger()
{
}

void Costume_wirehanger::Start()
{
	Player_ItemCostume::Start();
	m_RenderHead->SetRenderScale({ 64, 128 });
	m_RenderHead->CreateAnimation(L"DownFire", L"costume_wirehanger.bmp", 0, 1, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightFire", L"costume_wirehanger.bmp", 2, 3, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftFire", L"costume_wirehanger.bmp", 6, 7, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpFire", L"costume_wirehanger.bmp", 4, 5, 0.2f, true, false);

	m_RenderHead->CreateAnimation(L"DownIdle", L"costume_wirehanger.bmp", 0, 0, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightIdle", L"costume_wirehanger.bmp", 2, 2, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftIdle", L"costume_wirehanger.bmp", 6, 6, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpIdle", L"costume_wirehanger.bmp", 4, 4, 0.2f, true, false);
	m_RenderHead->ChangeAnimation(L"DownIdle");
}

void Costume_wirehanger::Update()
{
}
