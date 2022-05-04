#include "Fly.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Fly::Fly() : m_Collision(nullptr)
, m_Target(nullptr)
, m_Angle(0.f)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)
{
}

Fly::~Fly()
{
}

void Fly::Start()
{
	Enemy::Start();
	SetClassType(L"Fly");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 128, 128 });
		m_RenderBody->CreateAnimation(L"Idle", L"flyidle.bmp", 5, 6, 0.1f);
		m_RenderBody->CreateAnimation(L"Die", L"fiyDie.bmp", 0, 10, 0.05f, false);
		m_RenderBody->ChangeAnimation(L"Idle");



		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 128, 128 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"flyidleHit.bmp", 5, 6, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();

	}

	//충돌
	{

		m_Collision= CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Fly::StartCol);
		m_Collision->AddStayEvent(this, &Fly::StayCol);
		m_Collision->AddEndEvent(this, &Fly::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Fly::Update()
{
	Enemy::Update();
	EngineSound::Play(L"insect_swarm_loop.mp3", true, 0);
	m_MoveTime += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_MoveTime > 0.5f)
	{
		m_MoveTime = 0.f;
		m_Rad = float4::GetRandomAngleRad();
	}
}

void Fly::DebugRender()
{
	Enemy::DebugRender();
}

void Fly::BossTarget(EngineActor* _Target)
{
	m_Target = _Target;
	SetParentBase(_Target);
}

void Fly::TargetOut()
{
	float4 pos = GetPosition();
	SetParentBase(nullptr);
	m_Target = nullptr;
	SetPosition(pos);
}
