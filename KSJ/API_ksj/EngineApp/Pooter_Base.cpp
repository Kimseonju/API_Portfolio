#include "Pooter.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
#include "CCharacterInfo.h"
//static
//static func


Pooter::Pooter() : m_Collision(nullptr)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)
{
}

Pooter::~Pooter()
{
	int a = 0;
}

void Pooter::Start()
{
	Enemy::Start();
	SetClassType(L"Pooter");

	SetSize({ 30.f,40.f });

	m_CharacterInfo->SetAttackDelayMax(2.f);
	m_CharacterInfo->SetMaxSpeed(100.f);
	m_CharacterInfo->SetHP(3);
	m_CharacterInfo->SetSpeed(10.f);


	m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->CreateAnimation(L"Idle", L"Pooter.bmp", 0, 1, 0.05f);
	m_RenderBody->CreateAnimation(L"Attack", L"Pooter.bmp", 2, 15, 0.03f, false);
	m_RenderBody->CreateAnimation(L"Die", L"fiyDie.bmp", 0, 10, 0.05f, false);
	m_RenderBody->ChangeAnimation(L"Idle");

	{
		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Pooter::StartCol);
		m_Collision->AddStayEvent(this, &Pooter::StayCol);
		m_Collision->AddEndEvent(this, &Pooter::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 35 });
		NewShadow->SetAlpha(100);
	}
	m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
	m_RenderHitLayer->SetRenderScale({ 64, 64 });
	m_RenderHitLayer->CreateAnimation(L"Idle", L"PooterHit.bmp", 0, 1, 0.05f);
	m_RenderHitLayer->CreateAnimation(L"Attack", L"PooterHit.bmp", 2, 15, 0.03f, false);
	m_RenderHitLayer->ChangeAnimation(L"Idle");
	m_RenderHitLayer->SetAlpha(150);
	m_RenderHitLayer->RenderOff();
}

void Pooter::Update()
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

void Pooter::DebugRender()
{
	Enemy::DebugRender();
}

