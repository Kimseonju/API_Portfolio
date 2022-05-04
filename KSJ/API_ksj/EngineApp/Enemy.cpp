#include "Enemy.h"
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include <EngineCollision.h>
#include "LogicValue.h"
#include "Player.h"
#include "EnemyDieEffect.h"
#include "RoomInfo.h"
Enemy::Enemy() : m_RenderBody(nullptr), m_WallCollision(Dir::MAX), m_RoomInfo(nullptr), m_FSMDie(false)
, m_CharacterInfo(nullptr)
, m_MapCount(float4::ZERO)
, m_CheckDie(false)
, m_RenderHitLayer(nullptr)
, m_Time(0.f)
{

}

Enemy::~Enemy()
{
	if(m_CharacterInfo)
		delete m_CharacterInfo;
	m_CharacterInfo = nullptr;
}	


void Enemy::Start()
{
	m_CharacterInfo = new CCharacterInfo();
	GetMonsterFSM()->CreateState(L"Find", this, &Enemy::FindStay, &Enemy::FindStart, &Enemy::FindEnd);
	GetMonsterFSM()->CreateState(L"Move", this, &Enemy::MoveStay, &Enemy::MoveStart, &Enemy::MoveEnd);
	GetMonsterFSM()->CreateState(L"Attack", this, &Enemy::AttackStay, &Enemy::AttackStart, &Enemy::AttackEnd);
	GetMonsterFSM()->CreateState(L"Die", this, &Enemy::DieStay, &Enemy::DieStart, &Enemy::DieEnd);
	GetMonsterFSM()->ChangeState(L"Find");
	//방선택됬을때만 키기
	Off();
}

void Enemy::Update()
{
	m_MonsterFSM.Update();
	//몬스터는 가속도영향받는다 (눈물맞거나 폭탄맞으면 밀림)
	if ((m_FSMDie || m_CharacterInfo->GetHP()<=0) && !m_CheckDie)
	{
		m_MonsterFSM.ChangeState(L"Die");
		m_CheckDie = true;
	}
	if (nullptr != m_RenderHitLayer)
	{
		if (m_RenderHitLayer->IsRender())
		{
			m_Time += EngineTimer::MainTimer.GetFDeltaTime();
			if (m_Time > 0.2f)
			{
				m_Time = 0.f;
				m_RenderHitLayer->RenderOff();
			}
		}
	}
	
}

void Enemy::UpdateNext()
{
	m_CharacterInfo->Update();
	MapCollider();
	MovePosition(m_CharacterInfo->GetUpdateSpeed());
}

void Enemy::UpdatePrev()
{
}

void Enemy::DebugRender()
{
	EngineString PrintText;
	PrintText = L"Pos";
	PrintText += L" X ";
	PrintText += GetPosition().ix();
	PrintText += L" Y ";
	PrintText += GetPosition().iy();

	DebugTextout(PrintText, GetPosition().ix(), GetPosition().iy());
}

void Enemy::DieStart()
{
	m_CharacterInfo->StopSpeed();

	EnemyDieEffect* actor = GetScene()->CreateActor<EnemyDieEffect>();
	m_RoomInfo->PushActor(actor);
	actor->SetPosition(GetPosition());
	EngineSound::Play(L"Death_burst.mp3", false, 0);
	//적은 죽을때 피를 흩뿌리고죽는다.
	//여기에 코드작성
}
void Enemy::DieStay()
{
}

void Enemy::FSMDiePlay()
{
	m_FSMDie = true;
}

void Enemy::MapCollider()
{
	m_WallCollision = Dir::MAX;
	float4 pos = GetPosition();
	pos += m_CharacterInfo->GetUpdateSpeed();

	pos.x = static_cast<float>(pos.ix() % 960);
	pos.y = static_cast<float>(pos.iy() % 540);
	int Left = pos.ix() - GetSize().ihx();
	int Right = pos.ix() + GetSize().ihx();
	int Up = pos.iy() - GetSize().ihy();
	int Down = pos.iy() + GetSize().ihy();
	if (Left + m_CharacterInfo->GetUpdateSpeed().ix() < 102)
	{
		m_WallCollision = Dir::LEFT;
		if (m_CharacterInfo->GetDir().x != 1.f)
		{
			m_CharacterInfo->StopX();
		}
			
	}
	if (Right + m_CharacterInfo->GetUpdateSpeed().ix() > 850)
	{
		m_WallCollision = Dir::RIGHT;
		if (m_CharacterInfo->GetDir().x != -1.f)
		{
			m_CharacterInfo->StopX();
		}
	}

	if (Up + m_CharacterInfo->GetUpdateSpeed().iy() < 101)
	{
		m_WallCollision = Dir::UP;
		if (m_CharacterInfo->GetDir().y != 1.f)
		{
			m_CharacterInfo->StopY();
		}
			
	}
	if (Down + m_CharacterInfo->GetUpdateSpeed().iy() > 435)
	{
		m_WallCollision = Dir::DOWN;
		if (m_CharacterInfo->GetDir().y != -1.f)
		{
			m_CharacterInfo->StopY();
		}
			
	}
}

void Enemy::ColDirStop(float Angle)
{//오른쪽방향
	if (Angle > 315.f || Angle < 44.f)
	{
		if (m_CharacterInfo->GetDir().x != float4::RIGHT.x)
		{
			m_CharacterInfo->StopX();
		}

	}
	//왼쪽
	else if (Angle > 136.f && Angle < 224.f)
	{
		if (m_CharacterInfo->GetDir().x != float4::LEFT.x)
		{
			m_CharacterInfo->StopX();
		}
	}
	//위

	else if (Angle > 226.f && 314.f > Angle)
	{
		if (m_CharacterInfo->GetDir().y != float4::UP.y)
		{
			m_CharacterInfo->StopY();
		}
	}
	//아래
	else if (Angle > 46.f && 134.f > Angle) {

		if (m_CharacterInfo->GetDir().y != float4::DOWN.y)
			m_CharacterInfo->StopY();
	}
}
