#include "Horf.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Horf::Horf() : m_Collision(nullptr)
{
}

Horf::~Horf()
{
}

void Horf::Start()
{
	Enemy::Start();
	SetClassType(L"Horf");



	SetSize({ 50.f,50.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	m_CharacterInfo->SetAttackDelayMax(1.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Horf.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack", L"Horf.bmp", 1, 2, 0.5f, false);
		m_RenderBody->ChangeAnimation(L"Idle");



		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 64, 64 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"HorfHit.bmp", 0, 0, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"Attack", L"HorfHit.bmp", 1, 2, 0.5f, false);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Horf::StartCol);
		m_Collision->AddStayEvent(this, &Horf::StayCol);
		m_Collision->AddEndEvent(this, &Horf::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 36, 18 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Horf::Update()
{
	Enemy::Update();
}

void Horf::DebugRender()
{
	Enemy::DebugRender();
}
