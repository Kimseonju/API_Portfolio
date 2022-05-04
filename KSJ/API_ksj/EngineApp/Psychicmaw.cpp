#include "Psychicmaw.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Psychicmaw::Psychicmaw() : m_Collision(nullptr)
, m_RenderEffect(nullptr)
{
}

Psychicmaw::~Psychicmaw()
{
}

void Psychicmaw::Start()
{
	Enemy::Start();
	SetClassType(L"Psychicmaw");



	SetSize({ 50.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(6);
	GetCharacterInfo()->SetSpeed(10.f);
	m_CharacterInfo->SetAttackDelayMax(3.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Psychicmaw.bmp", 0, 0, 0.1f);
		m_RenderBody->ChangeAnimation(L"Idle");


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 64, 64 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"PsychicmawHit.bmp", 0, 0, 0.1f);
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
		m_Collision->AddStartEvent(this, &Psychicmaw::StartCol);
		m_Collision->AddStayEvent(this, &Psychicmaw::StayCol);
		m_Collision->AddEndEvent(this, &Psychicmaw::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 36, 18 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Psychicmaw::Update()
{
	Enemy::Update();
}

void Psychicmaw::DebugRender()
{
	Enemy::DebugRender();
}
