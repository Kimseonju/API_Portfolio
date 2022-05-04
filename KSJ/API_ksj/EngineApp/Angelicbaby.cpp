#include "Angelicbaby.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Angelicbaby::Angelicbaby() : m_Collision(nullptr)
{
}

Angelicbaby::~Angelicbaby()
{
}

void Angelicbaby::Start()
{
	Enemy::Start();
	SetClassType(L"Angelicbaby");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 128, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Angelicbaby.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack", L"Angelicbaby.bmp", 1, 1, 0.5f, false);
		m_RenderBody->ChangeAnimation(L"Idle");

	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>((int)LogicValue::CollisionGroup::Enemy);
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Angelicbaby::StartCol);
		m_Collision->AddStayEvent(this, &Angelicbaby::StayCol);
		m_Collision->AddEndEvent(this, &Angelicbaby::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>((int)LogicValue::RenderGroup::Shadow);
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Angelicbaby::Update()
{
	Enemy::Update();
}

void Angelicbaby::DebugRender()
{
	Enemy::DebugRender();
}
