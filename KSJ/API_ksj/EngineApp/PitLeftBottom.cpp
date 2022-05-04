#include "PitLeftBottom.h"

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
PitLeftBottom::PitLeftBottom() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitLeftBottom::~PitLeftBottom()
{

}
// member Func

void PitLeftBottom::Start()
{
	SetClassType(L"PitLeftBottom");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 5);


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitLeftBottom::StartCol);
	m_Collision->AddStayEvent(this, &PitLeftBottom::StayCol);
	m_Collision->AddEndEvent(this, &PitLeftBottom::EndCol);
}
void PitLeftBottom::Update()
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

void PitLeftBottom::DebugRender()
{
}

void PitLeftBottom::OffTask()
{
}

void PitLeftBottom::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitLeftBottom::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitLeftBottom::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
