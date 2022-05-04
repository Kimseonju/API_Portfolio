#include "HeartEffect.h"
#include <EngineRendererAnim.h>
#include "LogicValue.h"
//static
//static func


HeartEffect::HeartEffect() : m_RenderBody(nullptr)
{
}

HeartEffect::~HeartEffect()
{
}

void HeartEffect::Start()
{
	m_RenderBody = CreateRenderer<EngineRendererAnim>(static_cast<int>(LogicValue::RenderGroup::ItemEffect));
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->CreateAnimation(L"Idle", L"Hearteffect.bmp", 0, 9, 0.1f, false);
	m_RenderBody->ChangeAnimation(L"Idle");
	m_RenderBody->SetPivotPos({ 0.f, -30.f });

}

void HeartEffect::Update()
{
	if (nullptr != m_RenderBody)
	{
		if (m_RenderBody->IsEndAni())
		{
			Death();
		}
			
	}
}
