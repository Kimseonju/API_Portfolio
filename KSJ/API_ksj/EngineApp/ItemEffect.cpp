#include "ItemEffect.h"
#include <EngineRendererBasic.h>
#include "RoomInfo.h"
//static
//static func

ItemEffect::ItemEffect() :m_ItemUIEffect(nullptr), Alpha(0), m_TimeSize(0.f)
, m_Timer(0.f)
, m_Move(10.f)
, m_MoveTimer(1.f)
, m_Room(nullptr)
{
}

ItemEffect::~ItemEffect()
{
}

void ItemEffect::Start()
{
	m_ItemUIEffect = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::ItemUIEffect));
	m_ItemUIEffect->TransCut_Setting(L"giantbook_necronomicon.bmp", 0);
	m_ItemUIEffect->CamPosOff();
	m_ItemUIEffect->SetAlpha(254);
	float4 Size = EngineWindow::GetSize();
	m_ItemUIEffect->SetPivotPos({ Size.ihx(),Size.ihy() });
	m_ItemUIEffect->SetRenderScale(1);
	GetScene()->SetPause(true);
	FadeOutStart();
}

void ItemEffect::UpdateUI()
{
	m_Timer+= EngineTimer::MainTimer.GetFDeltaTime();

	if (m_Timer < 0.5f)
	{
		m_TimeSize += EngineTimer::MainTimer.GetFDeltaTime();
		m_ItemUIEffect->SetRenderScale({ m_TimeSize * 1000 });
	}
	
	else if (m_Timer < 1.3f)
	{
		m_TimeSize += EngineTimer::MainTimer.GetFDeltaTime()/6;
		m_ItemUIEffect->SetRenderScale({ m_TimeSize * 1000 });
		m_MoveTimer += EngineTimer::MainTimer.GetFDeltaTime();

		if (m_MoveTimer > 0.05f)
		{
			m_MoveTimer = 0.f;
			float4 Size = EngineWindow::GetSize();
			m_ItemUIEffect->SetPivotPos({ Size.hx() + m_Move,Size.hy() });
			m_Move = -m_Move;
		}
		return;
	}
	else 
	{
		m_ItemUIEffect->SetPosition({ 512.f ,512.f });
		FadeOut();
		m_TimeSize += EngineTimer::MainTimer.GetFDeltaTime()*2;
		m_ItemUIEffect->SetRenderScale({ m_TimeSize * 1000 });
	}

	if (0.f == Alpha)
	{
		FadeOutEnd();
	}
}


void ItemEffect::FadeOutStart()
{
	Alpha = 2.55f;
}

void ItemEffect::FadeOut()
{
	Alpha -= EngineTimer::MainTimer.GetFDeltaTime()*3;
	int iAlpha = 0;
	if (0.0f >= Alpha)
	{
		Alpha = 0.0f;
		iAlpha = 0;
	}
	else {
		iAlpha = static_cast<int>((Alpha * 100.0f));
	}
	m_ItemUIEffect->SetAlpha(iAlpha);
}

void ItemEffect::FadeOutEnd()
{
	if (m_Room)
	{
		m_Room->EnemyAllKill();
	}

	GetScene()->SetPause(false);
	m_ItemUIEffect->SetAlpha(0);
	Death();
}
