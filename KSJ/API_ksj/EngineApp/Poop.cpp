#include "Poop.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include <EngineWindowResMgr.h>

// Static Var
// Static Func

// member Var
Poop::Poop():
	m_RenderBody(nullptr), m_ImageCount(0), m_PoopHP(4), m_Collision(nullptr)
	, m_CheckSound(false)
{

}

Poop::~Poop()
{

}
// member Func

void Poop::Start()
{
	SetSize({ 50.f,50.f });
	SetClassType(L"Poop");

	m_RenderBody = CreateRenderer<EngineRendererBasic>(500);
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->TransCut_Setting(L"poop.bmp", 4- m_PoopHP);

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::MapObject));
	m_Collision->SetScale({ GetSize() });
	m_Collision->AddStartEvent(this, &Poop::StartCol);
	m_Collision->AddStayEvent(this, &Poop::StayCol);
	m_Collision->AddEndEvent(this, &Poop::EndCol);
}
void Poop::Update()
{
	if (m_PoopHP <= 0)
	{
		m_PoopHP = 0;
		m_Collision->Off();
		if (!m_CheckSound)
		{
			EngineSound::Play(L"pop.mp3", false, 0);
			m_CheckSound = true;
		}
		
	}
	m_RenderBody->TransCut_Setting(L"poop.bmp", 4 - m_PoopHP);


	
	
}
void Poop::DebugRender()
{
}
void Poop::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//체력은 4
	//데미지 입을때마다 m_ImageCount 이1 증가 후 다시 자르기
	//다 달면 동전 떨구기..?, 콜리전 사라짐
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::EnemyTear) ||
		_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_PoopHP--;

	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_PoopHP=0;
	}
}

void Poop::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Poop::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
