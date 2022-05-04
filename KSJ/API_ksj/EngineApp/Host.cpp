#include "Host.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Host::Host() : m_Collision(nullptr), m_bAttackStart(false)
, m_Timer(0.f)
, m_bFire(false)
, m_Invincible(true)
{
}

Host::~Host()
{
}

void Host::Start()
{
	Enemy::Start();
	SetClassType(L"Host");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	m_CharacterInfo->SetAttackDelayMax(2.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 128 });
		m_RenderBody->CreateAnimation(L"Idle", L"Host.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack", L"Host.bmp", 1, 1, 2.f, false);
		m_RenderBody->ChangeAnimation(L"Idle");


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 64, 128 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"HostHit.bmp", 0, 0, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"Attack", L"HostHit.bmp", 1, 1, 2.f, false);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->SetPivotPos({ 0.f,30.f });
		m_Collision->AddStartEvent(this, &Host::StartCol);
		m_Collision->AddStayEvent(this, &Host::StayCol);
		m_Collision->AddEndEvent(this, &Host::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Host::Update()
{
	Enemy::Update();
}

void Host::DebugRender()
{
	Enemy::DebugRender();
}
