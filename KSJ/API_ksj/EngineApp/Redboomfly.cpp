#include "Redboomfly.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Redboomfly::Redboomfly() : m_Collision(nullptr), m_Dir(0.5f)
{
}

Redboomfly::~Redboomfly()
{
}

void Redboomfly::Start()
{
	Enemy::Start();
	SetClassType(L"Redboomfly");



	SetSize({ 50.f,55.f });
	GetCharacterInfo()->SetMaxSpeed(200.f);
	GetCharacterInfo()->SetHP(3);
	GetCharacterInfo()->SetSpeed(30.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"Idle", L"Redboomfly.bmp", 0, 1, 0.1f);
		m_RenderBody->ChangeAnimation(L"Idle");


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 64, 64 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"RedboomflyHit.bmp", 0, 1, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Redboomfly::StartCol);
		m_Collision->AddStayEvent(this, &Redboomfly::StayCol);
		m_Collision->AddEndEvent(this, &Redboomfly::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 36, 18 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
	GetMonsterFSM()->ChangeState(L"Move");
}

void Redboomfly::Update()
{
	Enemy::Update();

	
}

void Redboomfly::DebugRender()
{
	Enemy::DebugRender();
}
