#include "PoofEffect.h"
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include <EngineCollision.h>
//static
//static func


PoofEffect::PoofEffect() : m_RenderEffect(nullptr)
{
}

PoofEffect::~PoofEffect()
{
}

void PoofEffect::Start()
{

	m_RenderEffect = CreateRenderer<EngineRendererAnim>(1);
	m_RenderEffect->SetRenderScale({ 192, 192 });
	m_RenderEffect->SetPivotPos({ 0.f,-50.f });
	m_RenderEffect->CreateAnimation(L"Play", L"Poof.bmp", 0, 14, 0.05f, false);
	m_RenderEffect->ChangeAnimation(L"Play");

}

void PoofEffect::Update()
{
	if (m_RenderEffect->IsEndAni())
	{
		Death();
	}
}

void PoofEffect::DebugRender()
{
}

void PoofEffect::FireObject()
{
	m_RenderEffect->SetRenderScale({ 96,96 });
}

