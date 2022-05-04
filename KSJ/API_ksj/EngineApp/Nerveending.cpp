#include "Nerveending.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Nerveending::Nerveending() : m_Collision(nullptr)
{
}

Nerveending::~Nerveending()
{
}

void Nerveending::Start()
{
	Enemy::Start();
	SetClassType(L"Nerveending");



	SetSize({ 30.f,50.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 48, 96 });
		m_RenderBody->CreateAnimation(L"Idle", L"Nerveending.bmp", 0, 5, 0.1f);
		m_RenderBody->ChangeAnimation(L"Idle");



		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 48, 96 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"NerveendingHit.bmp", 0, 5, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Nerveending::StartCol);
		m_Collision->AddStayEvent(this, &Nerveending::StayCol);
		m_Collision->AddEndEvent(this, &Nerveending::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Nerveending::Update()
{
	Enemy::Update();
}

void Nerveending::DebugRender()
{
	Enemy::DebugRender();
}
