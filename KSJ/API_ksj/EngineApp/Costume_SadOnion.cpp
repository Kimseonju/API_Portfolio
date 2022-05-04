#include "Costume_SadOnion.h"
#include <EngineRendererAnim.h>
//static
//static func


Costume_SadOnion::Costume_SadOnion()
{
}

Costume_SadOnion::~Costume_SadOnion()
{
}

void Costume_SadOnion::Start()
{
	Player_ItemCostume::Start();
	m_RenderHead->SetRenderScale({ 128, 128 });
	m_RenderHead->CreateAnimation(L"DownFire", L"Costume_Sadonion.bmp",  0, 2, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightFire", L"Costume_Sadonion.bmp", 3, 5, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftFire", L"Costume_Sadonion.bmp",  6, 8, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpFire", L"Costume_Sadonion.bmp",    0, 2, 0.2f, true, false);
	
	m_RenderHead->CreateAnimation(L"DownIdle", L"Costume_Sadonion.bmp",  0, 2, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightIdle", L"Costume_Sadonion.bmp", 3, 5, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftIdle", L"Costume_Sadonion.bmp",  6, 8, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpIdle", L"Costume_Sadonion.bmp",    0, 2, 0.2f, true, false);
	m_RenderHead->ChangeAnimation(L"DownIdle");
}

void Costume_SadOnion::Update()
{
}
void Costume_SadOnion::SetAnimFrameTimer(float _Time)
{
	m_RenderHead->SetAllAnimTimer(0.2f);
}
