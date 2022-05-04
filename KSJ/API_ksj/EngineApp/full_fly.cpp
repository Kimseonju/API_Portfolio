#include "full_fly.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


full_fly::full_fly() : m_Collision(nullptr)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)

{
}

full_fly::~full_fly()
{
}

void full_fly::Start()
{
	Enemy::Start();
	SetClassType(L"full_fly");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(4);
	GetCharacterInfo()->SetSpeed(20.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"full_fly.bmp", 0, 1, 0.05f);
		m_RenderBody->ChangeAnimation(L"Idle");



		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 64, 64 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"full_flyHit.bmp", 0, 1, 0.05f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &full_fly::StartCol);
		m_Collision->AddStayEvent(this, &full_fly::StayCol);
		m_Collision->AddEndEvent(this, &full_fly::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 30, 18 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void full_fly::Update()
{
	Enemy::Update();
	m_MoveTime += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_MoveTime > 0.5f)
	{
		m_MoveTime = 0.f;
		m_Rad = float4::GetRandomAngleRad();
	}
	EngineSound::Play(L"insect_swarm_loop.mp3", true, 0);
}

void full_fly::DebugRender()
{
	Enemy::DebugRender();
}
