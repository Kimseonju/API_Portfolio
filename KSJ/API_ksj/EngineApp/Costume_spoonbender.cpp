#include "Costume_spoonbender.h"
#include <EngineRendererAnim.h>
//static
//static func


Costume_spoonbender::Costume_spoonbender()
{
}

Costume_spoonbender::~Costume_spoonbender()
{
}

void Costume_spoonbender::Start()
{
	Player_ItemCostume::Start();
	m_RenderHead->SetRenderScale({ 64, 64 });
	m_RenderHead->CreateAnimation(L"DownFire", L"costume_spoonbender.bmp", 0, 1, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightFire", L"costume_spoonbender.bmp", 2, 3, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftFire", L"costume_spoonbender.bmp", 6, 7, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpFire", L"costume_spoonbender.bmp", 4, 5, 0.2f, true, false);

	m_RenderHead->CreateAnimation(L"DownIdle", L"costume_spoonbender.bmp", 1, 1, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightIdle", L"costume_spoonbender.bmp", 3, 3, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftIdle", L"costume_spoonbender.bmp", 7, 7, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpIdle", L"costume_spoonbender.bmp", 5, 5, 0.2f, true, false);
	m_RenderHead->ChangeAnimation(L"DownIdle");
}

void Costume_spoonbender::Update()
{
}
