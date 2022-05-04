#include "PitLeft.h"

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
PitLeft::PitLeft() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitLeft::~PitLeft()
{

}
// member Func

void PitLeft::Start()
{
	SetClassType(L"PitLeft");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 8);


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitLeft::StartCol);
	m_Collision->AddStayEvent(this, &PitLeft::StayCol);
	m_Collision->AddEndEvent(this, &PitLeft::EndCol);
}
void PitLeft::Update()
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

void PitLeft::DebugRender()
{
}

void PitLeft::OffTask()
{
}

void PitLeft::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//ĳ�����϶� �̵��������� �и���
	//�����϶� �̵��������� �и��� (��������)
}

void PitLeft::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitLeft::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
