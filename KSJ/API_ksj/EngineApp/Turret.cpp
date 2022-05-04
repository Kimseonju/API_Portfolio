#include "Turret.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Turret::Turret() : m_Collision(nullptr)
{
}

Turret::~Turret()
{
}

void Turret::Start()
{
	Enemy::Start();
	SetClassType(L"Turret");



	SetSize({ 50.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	m_CharacterInfo->SetAttackDelayMax(2.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Turret.bmp", 0, 0, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack", L"Turret.bmp", 3, 8, 0.05f, false);
		m_RenderBody->CreateAnimation(L"Die", L"Turret.bmp", 0, 2, 0.1f,false);
		m_RenderBody->ChangeAnimation(L"Idle");

	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::MapEnemyObject));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Turret::StartCol);
		m_Collision->AddStayEvent(this, &Turret::StayCol);
		m_Collision->AddEndEvent(this, &Turret::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Turret::Update()
{
	Enemy::Update();
}

void Turret::DebugRender()
{
	Enemy::DebugRender();
}
