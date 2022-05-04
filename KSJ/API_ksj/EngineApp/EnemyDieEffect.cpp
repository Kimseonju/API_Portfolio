#include "EnemyDieEffect.h"
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include <EngineCollision.h>
//static
//static func


EnemyDieEffect::EnemyDieEffect() : m_RenderEffect(nullptr)
, m_time(0.f)
{
}

EnemyDieEffect::~EnemyDieEffect()
{
}

void EnemyDieEffect::Start()
{

	m_RenderEffect = CreateRenderer<EngineRendererAnim>(1);
	m_RenderEffect->SetRenderScale({ 146, 112 });
	m_RenderEffect->CreateAnimation(L"Play", L"EnemyDie.bmp", 0, 8, 0.05f, false);
	m_RenderEffect->ChangeAnimation(L"Play");

}

void EnemyDieEffect::Update()
{
	m_time += EngineTimer::MainTimer.GetFDeltaTime();
	
	if (m_time > 5.f)
	{
		Death();
	}
}

void EnemyDieEffect::DebugRender()
{
}

void EnemyDieEffect::SelectPoop()
{
	m_RenderEffect->CreateAnimation(L"Playpoop", L"EnemyDiepoop.bmp", 0, 8, 0.05f, false);
	m_RenderEffect->ChangeAnimation(L"Playpoop");
}
