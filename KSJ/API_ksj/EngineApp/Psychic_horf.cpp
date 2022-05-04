#include "Psychic_horf.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Psychic_horf::Psychic_horf() : m_Collision(nullptr), m_RenderEffect(nullptr)
{
}

Psychic_horf::~Psychic_horf()
{
}

void Psychic_horf::Start()
{
	Enemy::Start();
	SetClassType(L"Psychic_horf");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	m_CharacterInfo->SetAttackDelayMax(3.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 96, 96 });
		m_RenderBody->CreateAnimation(L"Idle", L"Psychic_horf.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack", L"Psychic_horf.bmp", 1, 1, 0.3f);
		m_RenderBody->CreateAnimation(L"AttackEnd", L"Psychic_horf.bmp", 2, 2, 0.3f);
		m_RenderBody->ChangeAnimation(L"Idle");


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 96, 96 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"Psychic_horfHit.bmp", 0, 0, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"Attack", L"Psychic_horfHit.bmp", 1, 1, 0.3f);
		m_RenderHitLayer->CreateAnimation(L"AttackEnd", L"Psychic_horfHit.bmp", 2, 2, 0.3f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();



		m_RenderEffect = CreateRenderer<EngineRendererAnim>(500);
		m_RenderEffect->SetRenderScale({ 32, 32 });
		m_RenderEffect->CreateAnimation(L"Idle", L"PsychicEffect.bmp", 0, 6, 0.1f);
		m_RenderEffect->ChangeAnimation(L"Idle");
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Psychic_horf::StartCol);
		m_Collision->AddStayEvent(this, &Psychic_horf::StayCol);
		m_Collision->AddEndEvent(this, &Psychic_horf::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Psychic_horf::Update()
{
	Enemy::Update();
}

void Psychic_horf::DebugRender()
{
	Enemy::DebugRender();
}
