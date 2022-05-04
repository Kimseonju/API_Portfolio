#include "Item.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
// Static Var
LogicValue::ItemGroup Item::ItemNumber = LogicValue::ItemGroup::haloofflies;
// Static Func

// member Var
Item::Item():
	m_ItemRenderer(nullptr),
	m_MoveCount(0.0f),
	m_MaxCount(0.2f),
	m_MaxMove(5),
	m_Move(0),
	m_Up(true),
	m_Speed(10),
	m_ItemNumber(LogicValue::ItemGroup::MAX),
	m_Itemaltar(nullptr)
{

}

Item::~Item()
{

}
// member Func

void Item::Start()
{

	{
		m_ItemRenderer = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Item));
		NextItem();
	}

}
void Item::Update()
{
	m_MoveCount += EngineTimer::FDeltaTime();
	if (m_MoveCount >= m_MaxCount)
	{
		m_MoveCount = 0.f;
		if (m_Up)
		{
			if (m_Move >= m_MaxMove)
			{
				m_Up = false;
				--m_Move;
			}
			else
			{
				++m_Move;
			}
		}
		else
		{
			if (m_Move <= 0)
			{
				m_Up = true;
				++m_Move;
			}
			else
			{
				--m_Move;
			}
		}
	}
	float4 Pos = m_ItemRenderer->GetPivotPos();
	if (m_Up)
	{
		Pos.y += -1*EngineTimer::FDeltaTime()* m_Speed;
	}
	else
	{
		Pos.y += +1 * EngineTimer::FDeltaTime()* m_Speed;
	}
	if (Pos.y < -40.f)
	{
		Pos.y = -40.f;
	}
	m_ItemRenderer->SetPivotPos(Pos);
}

