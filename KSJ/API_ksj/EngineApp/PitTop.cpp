#include "PitTop.h"

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
PitTop::PitTop() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitTop::~PitTop()
{

}
// member Func

void PitTop::Start()
{
	SetClassType(L"PitTop");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 2);


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitTop::StartCol);
	m_Collision->AddStayEvent(this, &PitTop::StayCol);
	m_Collision->AddEndEvent(this, &PitTop::EndCol);
}
void PitTop::Update()
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

void PitTop::DebugRender()
{
}

void PitTop::OffTask()
{
}

void PitTop::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitTop::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitTop::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
