#include "Deathshead.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include "Player.h"
#include <EngineCollision.h>
#include <EngineRendererBasic.h>
//static
//static func


Deathshead::Deathshead() : m_Collision(nullptr), m_Dir(0.5f)
{
}

Deathshead::~Deathshead()
{
}

void Deathshead::Start()
{
	Enemy::Start();
	SetClassType(L"Deathshead");



	SetSize({ 30.f,40.f });
	GetCharacterInfo()->SetMaxSpeed(200.f);
	GetCharacterInfo()->SetHP(2);
	GetCharacterInfo()->SetSpeed(40.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 256, 256 });
		m_RenderBody->CreateAnimation(L"Idle", L"Deathshead.bmp", 0, 4, 0.1f);
		m_RenderBody->CreateAnimation(L"Die", L"Deathshead.bmp", 5, 9, 0.1f, false);
		m_RenderBody->ChangeAnimation(L"Idle");

	}

	//충돌
	{

		m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		m_Collision->SetScale({ GetSize() });
		m_Collision->AddStartEvent(this, &Deathshead::StartCol);
		m_Collision->AddStayEvent(this, &Deathshead::StayCol);
		m_Collision->AddEndEvent(this, &Deathshead::EndCol);
	}

	{
		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 36, 18 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
	m_MonsterFSM.ChangeState(L"Move");
}

void Deathshead::Update()
{
	Enemy::Update();
	
}

void Deathshead::DebugRender()
{
	Enemy::DebugRender();
}
