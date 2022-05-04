#include "Spikes.h"

#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include <EngineScene.h>
#include "LogicValue.h"
#include "Core.h"
#include "Player.h"

// Static Var
// Static Func

// member Var
Spikes::Spikes() : m_RenderBody(nullptr), m_Count(0.f), m_CountMax(3.0f), m_State(true), m_Collision(nullptr)


{

}

Spikes::~Spikes()
{

}
// member Func

void Spikes::Start()
{
	SetSize({ 12.f,12.f });
	SetClassType(L"Spikes");



	m_RenderBody = CreateRenderer<EngineRendererAnim>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->CreateAnimation(L"Idle", L"Spikes.bmp", 0, 0);
	m_RenderBody->CreateAnimation(L"AttackStart", L"Spikes.bmp", 0, 4,0.1f, false);
	m_RenderBody->CreateAnimation(L"AttackEnd", L"Spikes.bmp", 0, 4, 0.1f, false, true);
	m_RenderBody->ChangeAnimation(L"Idle");


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Spikes));
	m_Collision->SetScale({ 64, 64 });
	m_Collision->AddStartEvent(this, &Spikes::StartCol);
	m_Collision->AddStayEvent(this, &Spikes::StayCol);
	m_Collision->AddEndEvent(this, &Spikes::EndCol);
	m_Collision->Off();
}
void Spikes::Update()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		m_Collision->Off();
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		m_Collision->Off();
		return;
	}

	m_Count += EngineTimer::MainTimer.GetFDeltaTime();
	if (m_Count >= m_CountMax)
	{
		//true은 공격 false은 방어 
		if (m_State)
		{
			m_RenderBody->ChangeAnimation(L"AttackStart");
			m_Collision->On();
			m_State=!m_State;
			
		}
		else
		{
			m_RenderBody->ChangeAnimation(L"AttackEnd");
			m_Collision->Off();
			m_State = !m_State;
		}
		m_Count = 0.f;
	}

}

void Spikes::DebugRender()
{
}

void Spikes::OffTask()
{
	m_Count = 0.f;
}

void Spikes::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void Spikes::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void Spikes::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
