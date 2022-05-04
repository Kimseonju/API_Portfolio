#include "PitCenter.h"

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
PitCenter::PitCenter() : m_RenderBody(nullptr), m_Collision(nullptr)
{

}

PitCenter::~PitCenter()
{

}
// member Func

void PitCenter::Start()
{
	SetClassType(L"PitCenter");

	SetSize({ 48.f, 48.f });
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Pit));
	m_RenderBody->SetRenderScale({ 52.f, 52.f });
	m_RenderBody->TransCut_Setting(L"Pit.bmp", 1);

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Pit));
	m_Collision->SetScale({ 52.f,52.f });
	m_Collision->AddStartEvent(this, &PitCenter::StartCol);
	m_Collision->AddStayEvent(this, &PitCenter::StayCol);
	m_Collision->AddEndEvent(this, &PitCenter::EndCol);
}
void PitCenter::Update()
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

void PitCenter::DebugRender()
{
}

void PitCenter::OffTask()
{
}

void PitCenter::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//캐릭터일때 이동방향으로 밀리기
	//눈물일때 이동방향으로 밀리기 (눈물삭제)
}

void PitCenter::EndCol(EngineCollision* _This, EngineCollision* _Other)
{

}

void PitCenter::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
