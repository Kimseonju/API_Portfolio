#include "Deathshead.h"
#include "Player.h"
#include "LogicValue.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "CCharacterInfo.h"
#include "Core.h"
void Deathshead::FindStay()
{
	
}

void Deathshead::MoveStart()
{
	
}


void Deathshead::MoveStay()
{

	if (nullptr == LogicValue::MainPlayer)
	{
		m_CharacterInfo->SetDir(0.f);
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		m_CharacterInfo->SetDir(0.f);
		return;
	}
	m_CharacterInfo->SetDir(m_Dir);
	if (m_WallCollision == Dir::LEFT)
	{
		m_Dir.x += 1.f;
		m_CharacterInfo->StopSpeed();
	}
	if (m_WallCollision == Dir::RIGHT)
	{
		m_Dir.x += -1.f;
		m_CharacterInfo->StopSpeed();
	}
	if (m_WallCollision == Dir::UP)
	{
		m_Dir.y += 1.f;
		m_CharacterInfo->StopSpeed();
	}
	if (m_WallCollision == Dir::DOWN)
	{
		m_Dir.y -= 1.f;
		m_CharacterInfo->StopSpeed();
	}
}

void Deathshead::DieStart()
{
	m_CharacterInfo->StopSpeed();
	m_RenderBody->ChangeAnimation(L"Die");
	m_Collision->Off();
}

void Deathshead::DieStay()
{
	GetCharacterInfo()->StopSpeed();
	if (m_RenderBody->IsEndAni())
	{
		Death();
	}
}

void Deathshead::DieEnd()
{
}

void Deathshead::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}

void Deathshead::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Deathshead::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}
