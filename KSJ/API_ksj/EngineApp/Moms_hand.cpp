#include "Moms_hand.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Moms_hand::Moms_hand() : m_Collision(nullptr), m_Time(0.f), m_Shadow(nullptr)
{
}
Moms_hand::~Moms_hand()
{
}

void Moms_hand::Start()
{
	Enemy::Start();
	SetClassType(L"Moms_hand");


	SetSize({ 150.f,70.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(40.f);
	m_CharacterInfo->SetAttackDelayMax(3.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 192, 256 });
		m_RenderBody->SetPivotPos({ 0.f, -500.f+10.f });
		m_RenderBody->CreateAnimation(L"Idle", L"Moms_hand.bmp", 0, 0, 0.1f, true);
		m_RenderBody->CreateAnimation(L"AttackStart", L"Moms_hand.bmp", 2, 2, 0.1f);
		m_RenderBody->CreateAnimation(L"AttackEnd", L"Moms_hand.bmp", 3, 4, 1.f, false);

		m_RenderBody->CreateAnimation(L"MoveBack", L"Moms_hand.bmp", 5, 9, 0.2f, false);
		m_RenderBody->ChangeAnimation(L"Idle");



		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 192, 256 });
		m_RenderHitLayer->SetPivotPos({ 0.f, -500.f + 10.f });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"Moms_handHit.bmp", 0, 0, 0.1f, true);
		m_RenderHitLayer->CreateAnimation(L"AttackStart", L"Moms_handHit.bmp", 2, 2, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"AttackEnd", L"Moms_handHit.bmp", 3, 4, 1.f, false);

		m_RenderHitLayer->CreateAnimation(L"MoveBack", L"Moms_handHit.bmp", 5, 9, 0.2f, false);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->SetPivotPos({ 0.f, 20.f });
		m_Collision->AddStartEvent(this, &Moms_hand::StartCol);
		m_Collision->AddStayEvent(this, &Moms_hand::StayCol);
		m_Collision->AddEndEvent(this, &Moms_hand::EndCol);
		m_Collision->Off();
	}

	{
		m_Shadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		m_Shadow->TransCut_Setting(L"shadow.bmp", 0);
		m_Shadow->SetRenderScale({ 160, 60 });
		m_Shadow->SetPivotPos({ 0.f, 30.f });
		m_Shadow->SetAlpha(100);
	}
}

void Moms_hand::Update()
{
	Enemy::Update();
	if (nullptr !=m_RenderHitLayer)
	{
		m_RenderHitLayer->SetPivotPos(m_RenderBody->GetPivotPos());
	}
	
}

void Moms_hand::DebugRender()
{
	Enemy::DebugRender();
}
