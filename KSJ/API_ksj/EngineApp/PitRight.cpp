#include "PitRight.h"

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
PitRight::PitRight() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitRight::~PitRight()
{

}
// member Func

void PitRight::Start()
{
	SetClassType(L"PitRight");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 9);


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitRight::StartCol);
	m_Collision->AddStayEvent(this, &PitRight::StayCol);
	m_Collision->AddEndEvent(this, &PitRight::EndCol);
}
void PitRight::Update()
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

void PitRight::DebugRender()
{
}

void PitRight::OffTask()
{
}

void PitRight::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitRight::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitRight::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
