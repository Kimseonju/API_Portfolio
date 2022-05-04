#include "PitLeftTop.h"

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
PitLeftTop::PitLeftTop() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitLeftTop::~PitLeftTop()
{

}
// member Func

void PitLeftTop::Start()
{
	SetClassType(L"PitLeftTop");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 6);

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitLeftTop::StartCol);
	m_Collision->AddStayEvent(this, &PitLeftTop::StayCol);
	m_Collision->AddEndEvent(this, &PitLeftTop::EndCol);
}
void PitLeftTop::Update()
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

void PitLeftTop::DebugRender()
{
}

void PitLeftTop::OffTask()
{
}

void PitLeftTop::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitLeftTop::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitLeftTop::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
