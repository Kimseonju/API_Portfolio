#include "Boomfly.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Boomfly::Boomfly() : m_Collision(nullptr), m_Dir(0.5f)
{
}

Boomfly::~Boomfly()
{
}

void Boomfly::Start()
{
	Enemy::Start();
	SetClassType(L"Boomfly");



	SetSize({ 50.f,55.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(3);
	GetCharacterInfo()->SetSpeed(30.f);
	//이미지
	{
		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Boomfly.bmp", 0, 1, 0.05f);
		m_RenderBody->ChangeAnimation(L"Idle");
	}

	//충돌
	{
		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Boomfly::StartCol);
		m_Collision->AddStayEvent(this, &Boomfly::StayCol);
		m_Collision->AddEndEvent(this, &Boomfly::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 48, 24 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
	GetMonsterFSM()->ChangeState(L"Move");


	m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
	m_RenderHitLayer->SetRenderScale({ 64, 64 });
	m_RenderHitLayer->CreateAnimation(L"Idle", L"BoomflyHit.bmp", 0, 1, 0.05f);
	m_RenderHitLayer->ChangeAnimation(L"Idle");
	m_RenderHitLayer->SetAlpha(150);
	m_RenderHitLayer->RenderOff();
}

void Boomfly::Update()
{
	Enemy::Update();
	EngineSound::Play(L"insect_swarm_loop.mp3", true, 0);
}

void Boomfly::DebugRender()
{
	Enemy::DebugRender();
}
