#include "Costume_catoninetails.h"
#include <EngineRendererAnim.h>
//static
//static func


Costume_catoninetails::Costume_catoninetails()
{
}

Costume_catoninetails::~Costume_catoninetails()
{
}

void Costume_catoninetails::Start()
{
	Player_ItemCostume::Start();
	m_RenderHead->SetRenderScale({ 64, 64 });
	m_RenderHead->CreateAnimation(L"DownFire", L"costume_catoninetails.bmp", 0, 1, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightFire", L"costume_catoninetails.bmp", 2, 3, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftFire", L"costume_catoninetails.bmp", 6, 7, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpFire", L"costume_catoninetails.bmp", 4, 5, 0.2f, true, false);

	m_RenderHead->CreateAnimation(L"DownIdle", L"costume_catoninetails.bmp", 1, 1, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"RightIdle", L"costume_catoninetails.bmp", 3, 3, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"LeftIdle", L"costume_catoninetails.bmp", 7, 7, 0.2f, true, false);
	m_RenderHead->CreateAnimation(L"UpIdle", L"costume_catoninetails.bmp", 5, 5, 0.2f, true, false);
	m_RenderHead->ChangeAnimation(L"DownIdle");
}

void Costume_catoninetails::Update()
{
}
