#include "Sucker.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Sucker::Sucker() : m_Collision(nullptr)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)
{
}

Sucker::~Sucker()
{
}

void Sucker::Start()
{
	Enemy::Start();
	SetClassType(L"Sucker");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Sucker.bmp", 0, 1, 0.1f);
		m_RenderBody->ChangeAnimation(L"Idle");



		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 64, 64 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"Sucker.bmp", 0, 1, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Sucker::StartCol);
		m_Collision->AddStayEvent(this, &Sucker::StayCol);
		m_Collision->AddEndEvent(this, &Sucker::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Sucker::Update()
{
	Enemy::Update();
	m_MoveTime += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_MoveTime > 0.5f)
	{
		m_MoveTime = 0.f;
		m_Rad = float4::GetRandomAngleRad();
	}
}

void Sucker::DebugRender()
{
	Enemy::DebugRender();
}
