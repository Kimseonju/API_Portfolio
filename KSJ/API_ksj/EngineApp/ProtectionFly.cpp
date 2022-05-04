#include "ProtectionFly.h"
#include <EngineRendererAnim.h>
#include <EngineCollision.h>
#include <EngineTimer.h>
#include "LogicValue.h"
#include <EngineRendererBasic.h>
//static
//static func


ProtectionFly::ProtectionFly():m_Angle(0.f), m_RenderBody(nullptr), m_Collision(nullptr)
{
}

ProtectionFly::~ProtectionFly()
{
}

void ProtectionFly::Start()
{
	SetClassType(L"ProtectionFly");
	SetSize({ 30.f,40.f });
	m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
	m_RenderBody->SetRenderScale({ 128, 128 });
	m_RenderBody->CreateAnimation(L"Idle", L"flyidle.bmp", 5, 6, 0.1f);
	m_RenderBody->ChangeAnimation(L"Idle");

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Protection));
	m_Collision->SetScale({ GetSize() });
	m_Collision->AddStartEvent(this, &ProtectionFly::StartCol);
	m_Collision->AddStayEvent(this, &ProtectionFly::StayCol);
	m_Collision->AddEndEvent(this, &ProtectionFly::EndCol);


	EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
	NewShadow->TransCut_Setting(L"shadow.bmp", 0);
	NewShadow->SetRenderScale({ 24, 12 });
	NewShadow->SetPivotPos({ 0, 30 });
	NewShadow->SetAlpha(100);
}

void ProtectionFly::Update()
{
	m_Angle += EngineTimer::FDeltaTime(60.f);
	float4 Dir = float4::AngleToDir2DDeg(m_Angle);
	m_RenderBody->SetPivotPos(Dir * 40.0f);
}

void ProtectionFly::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void ProtectionFly::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void ProtectionFly::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}
