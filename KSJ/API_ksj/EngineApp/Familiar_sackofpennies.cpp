#include "Familiar_sackofpennies.h"
#include <EngineRendererAnim.h>
#include "PickUpItem.h"	
//static
//static func


Familiar_sackofpennies::Familiar_sackofpennies()
{
}

Familiar_sackofpennies::~Familiar_sackofpennies()
{
}

void Familiar_sackofpennies::Start()
{
	Familiar::Start();
	m_RenderBody->CreateAnimation(L"DownFire", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"RightFire", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"LeftFire", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"UpFire", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);

	m_RenderBody->CreateAnimation(L"DownIdle", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"RightIdle", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"LeftIdle", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"UpIdle", L"familiar_sackofpennies.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->ChangeAnimation(L"DownIdle");
		
	m_RenderBody->CreateAnimation(L"Event", L"familiar_sackofpennies.bmp", 1, 4, 0.2f, false, false);
}

void Familiar_sackofpennies::Update()
{
	Familiar::Update();
	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"DownIdle");
	}
}

void Familiar_sackofpennies::FamiliarEvent()
{
	m_RenderBody->ChangeAnimation(L"Event");
	PickUpItem* item = GetScene()->CreateActor<PickUpItem>();

	item->SetPosition(GetPosition());
	item->SetCount(1);
	item->Init(LogicValue::ItemType::Coin);
}
