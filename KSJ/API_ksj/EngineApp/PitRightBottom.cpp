#include "PitRightBottom.h"

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
PitRightBottom::PitRightBottom() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitRightBottom::~PitRightBottom()
{

}
// member Func

void PitRightBottom::Start()
{
	SetClassType(L"PitRightBottom");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 4);


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitRightBottom::StartCol);
	m_Collision->AddStayEvent(this, &PitRightBottom::StayCol);
	m_Collision->AddEndEvent(this, &PitRightBottom::EndCol);
}
void PitRightBottom::Update()
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

void PitRightBottom::DebugRender()
{
}

void PitRightBottom::OffTask()
{
}

void PitRightBottom::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitRightBottom::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitRightBottom::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
