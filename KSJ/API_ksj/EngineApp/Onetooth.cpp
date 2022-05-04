#include "Onetooth.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Onetooth::Onetooth() : m_Collision(nullptr)
, m_Rad(float4::ZERO)
, m_MoveTime(0.f)
{
}

Onetooth::~Onetooth()
{
}

void Onetooth::Start()
{
	Enemy::Start();
	SetClassType(L"Onetooth");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(200.f);
	GetCharacterInfo()->SetHP(5);
	GetCharacterInfo()->SetSpeed(30.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 96, 96 });
		m_RenderBody->CreateAnimation(L"Idle", L"Onetooth.bmp", 0, 2, 0.1f);
		m_RenderBody->CreateAnimation(L"Move", L"Onetooth.bmp", 3, 5, 0.1f);
		m_RenderBody->ChangeAnimation(L"Idle");


		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 96, 96 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"OnetoothHit.bmp", 0, 2, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"Move", L"OnetoothHit.bmp", 3, 5, 0.1f);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->SetAlpha(150);
		m_RenderHitLayer->RenderOff();
	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Onetooth::StartCol);
		m_Collision->AddStayEvent(this, &Onetooth::StayCol);
		m_Collision->AddEndEvent(this, &Onetooth::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 36, 18 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
}

void Onetooth::Update()
{
	Enemy::Update(); m_MoveTime += EngineTimer::MainTimer.GetFDeltaTime();

	if (m_MoveTime > 1.f)
	{
		m_MoveTime = 0.f;
		m_Rad = float4::GetRandomAngleRad();
	}
}

void Onetooth::DebugRender()
{
	Enemy::DebugRender();
}
