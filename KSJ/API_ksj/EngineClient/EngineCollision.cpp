#include "EngineCollision.h"
#include "EngineActor.h"
//static
//static func


EngineCollision::EngineCollision():
	m_Type(COLTYPE::RECT), m_Order(0), m_Actor(nullptr), m_PivotPos(float4::ZERO), m_ColScale(float4::ZERO)
{
}

EngineCollision::~EngineCollision()
{

	for (size_t i = 0; i < StartEvent.size(); i++)
	{
		delete StartEvent[i];
	}
	StartEvent.clear();

	for (size_t i = 0; i < StayEvent.size(); i++)
	{
		delete StayEvent[i];
	}
	StayEvent.clear();
	for (size_t i = 0; i < EndEvent.size(); i++)
	{
		delete EndEvent[i];
	}
	EndEvent.clear();
}
void EngineCollision::CollisionDataUpdate()
{
	m_Data.Pos = GetActor()->GetPosition() + m_PivotPos;
}


void EngineCollision::Render()
{
	float4 CamPos=GetActor()->GetScene()->GetCamPos();
	m_Data.Pos =m_Data.Pos - CamPos;
	RECT	rc = { m_Data.iLeft(), m_Data.iUp(), m_Data.iRight(), m_Data.iDown() };

	FrameRect(EngineWindow::GetBackBufferDC(), &rc, nullptr);
}

void EngineCollision::CollisionCheck(EngineCollision* _Other)
{
	COLTYPE ThisColType = m_Type;
	COLTYPE OtherColType = _Other->m_Type;
	

	if (true==Coliison2DCheck::ColFunc[static_cast<int>(ThisColType)][static_cast<int>(OtherColType)](m_Data, _Other->m_Data))
	{
		if (m_ColSet.end() == m_ColSet.find(_Other))
		{
			UpdateStartEvent(this, _Other);
			_Other->UpdateStartEvent(_Other, this);
		}
		else
		{
			UpdateStayEvent(this, _Other);
			_Other->UpdateStayEvent(_Other, this);
		}
	}
	else
	{
		if (m_ColSet.end() != m_ColSet.find(_Other))
		{
			UpdateEndEvent(this, _Other);
			_Other->UpdateEndEvent(_Other, this);
		}
	}
}

void EngineCollision::ReleaseUpdate()
{
	// OFF를 하면 상대방에게서 나를 빼고 END를 호출해줘야 하는데.
	// DEATH와 동일하다.
	std::set<EngineCollision*>::iterator Start = m_ColSet.begin();
	std::set<EngineCollision*>::iterator End = m_ColSet.end();
	for (; Start != End;)
	{
		for (size_t i = 0; i < EndEvent.size(); i++)
		{
			EndEvent[i]->CallBack(this, (*Start));
		}
		// (*Start)->m_ColSet.erase(this);
		(*Start)->UpdateEndEvent(*Start, this);
		Start = m_ColSet.erase(Start);
	}
}


void EngineCollision::DeathTask()
{
	ReleaseUpdate();
}


void EngineCollision::OffTask()
{
	ReleaseUpdate();
}


float4 EngineCollision::GetPosition()const
{
	return m_Actor->GetPosition() + m_PivotPos;
}
