#include "Squirt.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Squirt::Squirt() : m_Collision(nullptr), m_Dir(float4::ZERO)
{
}

Squirt::~Squirt()
{
}

void Squirt::Start()
{
	Enemy::Start();
	SetClassType(L"Squirt");



	SetSize({ 50.f,50.f });
	m_CharacterInfo->SetMaxSpeed(0.f);
	m_CharacterInfo->SetHP(2);
	m_CharacterInfo->SetSpeed(100.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 128, 128 });
		m_RenderBody->CreateAnimation(L"RightIdle", L"Squirt.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"RightAttack", L"Squirt.bmp", 1, 2, 0.5f, false);
		m_RenderBody->CreateAnimation(L"RightAttacking", L"Squirt.bmp", 3, 4, 0.1f);

		m_RenderBody->CreateAnimation(L"LeftIdle", L"Squirt.bmp", 6, 6, 0.1f);
		m_RenderBody->CreateAnimation(L"LeftAttack", L"Squirt.bmp", 7, 8, 0.5f, false);
		m_RenderBody->CreateAnimation(L"LeftAttacking", L"Squirt.bmp", 9, 10, 0.1f);
		m_RenderBody->ChangeAnimation(L"RightIdle");




		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 128, 128 });
		m_RenderHitLayer->CreateAnimation(L"RightIdle", L"SquirtHit.bmp", 0, 0, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"RightAttack", L"SquirtHit.bmp", 1, 2, 0.5f, false);
		m_RenderHitLayer->CreateAnimation(L"RightAttacking", L"SquirtHit.bmp", 3, 4, 0.1f);

		m_RenderHitLayer->CreateAnimation(L"LeftIdle", L"SquirtHit.bmp", 6, 6, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"LeftAttack", L"SquirtHit.bmp", 7, 8, 0.5f, false);
		m_RenderHitLayer->CreateAnimation(L"LeftAttacking", L"SquirtHit.bmp", 9, 10, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"RightIdle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->SetPivotPos({ 0.f,10.f });
		m_Collision->AddStartEvent(this, &Squirt::StartCol);
		m_Collision->AddStayEvent(this, &Squirt::StayCol);
		m_Collision->AddEndEvent(this, &Squirt::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Squirt::Update()
{
	Enemy::Update();
}

void Squirt::DebugRender()
{
	Enemy::DebugRender();
}
