#include "PitBottom.h"

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
PitBottom::PitBottom() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitBottom::~PitBottom()
{

}
// member Func

void PitBottom::Start()
{
	SetClassType(L"PitBottom");

	SetSize({ 48.f, 48.f });



	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 0);


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitBottom::StartCol);
	m_Collision->AddStayEvent(this, &PitBottom::StayCol);
	m_Collision->AddEndEvent(this, &PitBottom::EndCol);
}
void PitBottom::Update()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}

}

void PitBottom::DebugRender()
{
}

void PitBottom::OffTask()
{
}

void PitBottom::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitBottom::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitBottom::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
