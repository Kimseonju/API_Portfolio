#include "EngineActor.h"
#include "EngineRenderer.h"
#include "EngineCollision.h"

EngineActor::EngineActor():
	m_Scene(nullptr),
	m_Position(float4::ZERO),
	m_Collision(0),
	m_Renderer(0)
{

}

EngineActor::~EngineActor()
{

	{
		std::list<EngineRenderer*>::iterator Start = m_Renderer.begin();
		std::list<EngineRenderer*>::iterator End = m_Renderer.end();
		for (; Start != End; ++Start)
		{
			delete (*Start);
			*Start = nullptr;
		}

		m_Renderer.clear();
	}
	{
		std::list<EngineCollision*>::iterator Start = m_Collision.begin();
		std::list<EngineCollision*>::iterator End = m_Collision.end();
		for (; Start != End; ++Start)
		{
			delete (*Start);
			*Start = nullptr;
		}

		m_Collision.clear();
	}
}

void EngineActor::OffTask() 
{
	{
		std::list<EngineRenderer*>::iterator Start = m_Renderer.begin();
		std::list<EngineRenderer*>::iterator End = m_Renderer.end();

		for (; Start != End; ++Start)
		{
			(*Start)->CallOffTask();
		}
	}
	{
		std::list<EngineCollision*>::iterator Start = m_Collision.begin();
		std::list<EngineCollision*>::iterator End = m_Collision.end();
		for (; Start != End; ++Start)
		{
			(*Start)->CallOffTask();
		}
	}

}

void EngineActor::OnTask()
{
	{
		std::list<EngineRenderer*>::iterator Start = m_Renderer.begin();
		std::list<EngineRenderer*>::iterator End = m_Renderer.end();

		for (; Start != End; ++Start)
		{
			(*Start)->CallOnTask();
		}
	}
	{
		std::list<EngineCollision*>::iterator Start = m_Collision.begin();
		std::list<EngineCollision*>::iterator End = m_Collision.end();
		for (; Start != End; ++Start)
		{
			(*Start)->CallOnTask();
		}
	}
}

void EngineActor::DeathTask()
{
	{
		std::list<EngineRenderer*>::iterator Start = m_Renderer.begin();
		std::list<EngineRenderer*>::iterator End = m_Renderer.end();

		for (; Start != End; ++Start)
		{
			(*Start)->DeathTask();
			(*Start)->Death();
		}
	}
	{
		std::list<EngineCollision*>::iterator Start = m_Collision.begin();
		std::list<EngineCollision*>::iterator End = m_Collision.end();
		for (; Start != End; ++Start)
		{
			(*Start)->DeathTask();
			(*Start)->Death();
		}
	}
}

void EngineActor::Release()
{
	{
		std::list<EngineRenderer*>::iterator Start = m_Renderer.begin();
		std::list<EngineRenderer*>::iterator End = m_Renderer.end();

		for (; Start != End; )
		{
			if (false == (*Start)->IsDeath())
			{
				++Start;
				continue;
			}
			(*Start)->DeathTask();
			delete (*Start);
			Start = m_Renderer.erase(Start);
		}
	}
	{
		std::list<EngineCollision*>::iterator Start = m_Collision.begin();
		std::list<EngineCollision*>::iterator End = m_Collision.end();
		for (; Start != End; )
		{
			if (false == (*Start)->IsDeath())
			{
				++Start;
				continue;
			}
			(*Start)->DeathTask();
			delete (*Start);
			Start = m_Collision.erase(Start);
		}
	}
}
