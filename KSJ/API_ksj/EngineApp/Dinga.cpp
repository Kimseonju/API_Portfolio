#include "Dinga.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Dinga::Dinga() : m_Collision(nullptr)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)
{
}

Dinga::~Dinga()
{
}

void Dinga::Start()
{
	Enemy::Start();
	SetClassType(L"Dinga");



	SetSize({ 80.f,80.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	m_CharacterInfo->SetAttackDelayMax(2.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 256, 256 });
		m_RenderBody->CreateAnimation(L"Idle", L"Dinga.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack", L"Dinga.bmp", 1, 3, 0.1f, false);
		m_RenderBody->ChangeAnimation(L"Idle");
		


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 256, 256 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"DingaHit.bmp", 0, 0, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"Attack", L"DingaHit.bmp", 1, 3, 0.1f, false);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();

	}
	
	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Dinga::StartCol);
		m_Collision->AddStayEvent(this, &Dinga::StayCol);
		m_Collision->AddEndEvent(this, &Dinga::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Dinga::Update()
{
	Enemy::Update();
	m_MoveTime += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_MoveTime > 0.5f)
	{
		m_MoveTime = 0.f;
		m_Rad = float4::GetRandomAngleRad();
	}
	
}

void Dinga::DebugRender()
{
	Enemy::DebugRender();
}
