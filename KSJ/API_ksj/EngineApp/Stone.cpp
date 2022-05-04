#include "Stone.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include "LogicValue.h"
#include <EngineCollision.h>
//static
//static func


Stone::Stone() : m_RenderBody(nullptr), m_Collision(nullptr)
{
}

Stone::~Stone()
{
}

void Stone::Start()
{
	SetSize({ 50.f,50.f });
	SetClassType(L"Stone");

	m_RenderBody = CreateRenderer<EngineRendererBasic>(500);
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->TransCut_Setting(L"rocks_basement.bmp", 0);

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::MapObject));
	m_Collision->SetScale({ GetSize() });
	m_Collision->AddStartEvent(this, &Stone::StartCol);
	m_Collision->AddStayEvent(this, &Stone::StayCol);
	m_Collision->AddEndEvent(this, &Stone::EndCol);
}
void Stone::Update()
{
}
void Stone::DebugRender()
{
}
void Stone::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		EngineSound::Play(L"rockBreak.mp3", false, 0);
		m_RenderBody->TransCut_Setting(L"rocks_basement.bmp", 3);
		m_Collision->Off();
	}
}

void Stone::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Stone::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
