#include "Familiar_littlechad.h"
#include <EngineRendererAnim.h>
#include "PickUpItem.h"
//static
//static func


Familiar_littlechad::Familiar_littlechad()
{
}

Familiar_littlechad::~Familiar_littlechad()
{
}

void Familiar_littlechad::Start()
{
	Familiar::Start();
	m_RenderBody->CreateAnimation(L"DownFire", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"RightFire", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"LeftFire", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"UpFire", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);

	m_RenderBody->CreateAnimation(L"DownIdle", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"RightIdle", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"LeftIdle", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"UpIdle", L"familiar_littlechad.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->ChangeAnimation(L"DownIdle");


	m_RenderBody->CreateAnimation(L"Event", L"familiar_littlechad.bmp", 1, 2, 0.2f, false, false);
}

void Familiar_littlechad::Update()
{
	Familiar::Update();
	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"DownIdle");
	}
}

void Familiar_littlechad::FamiliarEvent()
{
	m_RenderBody->ChangeAnimation(L"Event");
	PickUpItem* item = GetScene()->CreateActor<PickUpItem>();

	item->SetPosition(GetPosition());
	item->SetCount(1);
	item->Init(LogicValue::ItemType::Heart);
}
