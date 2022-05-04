#include "Dip.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Dip::Dip() : m_Collision(nullptr)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)
{
}

Dip::~Dip()
{
}

void Dip::Start()
{
	Enemy::Start();
	SetClassType(L"Dip");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(100.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(10.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 128, 128 });
		m_RenderBody->CreateAnimation(L"Move", L"Dip.bmp", 0, 4, 0.1f);
		m_RenderBody->ChangeAnimation(L"Move");


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 128, 128 });
		m_RenderHitLayer->CreateAnimation(L"Move", L"DipHit.bmp", 0, 4, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"Move");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Dip::StartCol);
		m_Collision->AddStayEvent(this, &Dip::StayCol);
		m_Collision->AddEndEvent(this, &Dip::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 24, 12 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Dip::Update()
{
	Enemy::Update(); 
	m_MoveTime += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_MoveTime > 0.5f)
	{
		m_MoveTime = 0.f;
		m_Rad = float4::GetRandomAngleRad();
	}
}

void Dip::DebugRender()
{
	Enemy::DebugRender();
}
