#include "FlyBoss.h"
#include "LogicValue.h"
#include <EngineWindowResMgr.h>
#include <EngineCollision.h>
#include "Fly.h"
#include "RoomInfo.h"
#include "Player.h"
#include "EnemyTear.h"
#include "Core.h"
#include <EngineRendererBasic.h>
//static
//static func


FlyBoss::FlyBoss() :m_Dir(0.5f)
{
}

FlyBoss::~FlyBoss()
{
}

void FlyBoss::Start()
{
	Enemy::Start();

	SetClassType(L"FlyBoss");

	SetSize({ 60.f,60.f });
	GetCharacterInfo()->SetHPMax(50);
	GetCharacterInfo()->SetHP(GetCharacterInfo()->GetHPMax());
	m_CharacterInfo->SetAttackDelayMax(2.f);
	GetCharacterInfo()->SetMaxSpeed(300.f);
	//이미지
	{

		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 160, 128 });
		m_RenderBody->CreateAnimation(L"Idle", L"duke.bmp", 1, 1, 0.1f);
		m_RenderBody->CreateAnimation(L"Attack_Start", L"duke.bmp", 2, 3, 0.3f, false);
		m_RenderBody->CreateAnimation(L"Attack_End", L"duke.bmp", 0, 0, 0.6f, false);
		m_RenderBody->ChangeAnimation(L"Idle");
		SetRenderBody(m_RenderBody);

		m_RenderHitLayer = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHitLayer->SetRenderScale({ 160, 128 });
		m_RenderHitLayer->CreateAnimation(L"Idle", L"dukeHit.bmp", 1, 1, 0.1f);
		m_RenderHitLayer->CreateAnimation(L"Attack_Start", L"dukeHit.bmp", 2, 3, 0.3f, false);
		m_RenderHitLayer->CreateAnimation(L"Attack_End", L"dukeHit.bmp", 0, 0, 0.6f, false);
		m_RenderHitLayer->ChangeAnimation(L"Idle");
		m_RenderHitLayer->RenderOff();
		m_RenderHitLayer->SetAlpha(150);
	}

	//충돌
	{
		EngineCollision* Col = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
		Col->SetScale({ GetSize() });
		Col->AddStartEvent(this, &FlyBoss::StartCol);
		Col->AddStayEvent(this, &FlyBoss::StayCol);
		Col->AddEndEvent(this, &FlyBoss::EndCol);
	}
	{

		EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		NewShadow->TransCut_Setting(L"shadow.bmp", 0);
		NewShadow->SetRenderScale({ 48, 24 });
		NewShadow->SetPivotPos({ 0, 30 });
		NewShadow->SetAlpha(100);
	}
	m_MonsterFSM.ChangeState(L"Move");
}

void FlyBoss::Update()
{
	std::list<Fly*>::iterator iter = m_AllFly.begin();
	std::list<Fly*>::iterator iterEnd = m_AllFly.end();
	for (; iter != iterEnd; )
	{
		if (false == (*iter)->IsDeath())
		{
			++iter;
			continue;
		}
		iter=m_AllFly.erase(iter);
	}

	Enemy::Update();
	//임시
	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"Idle");
		m_RenderHitLayer->ChangeAnimation(L"Idle");
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

void FlyBoss::DebugRender()
{
	Enemy::DebugRender();
}

void FlyBoss::MapCollider()
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
	if (Left + m_CharacterInfo->GetUpdateSpeed().ix() < 115)
	{
		m_WallCollision = Dir::LEFT;
		if (m_CharacterInfo->GetDir().x != 1.f)
		{
			m_CharacterInfo->StopX();
		}

	}
	if (Right + m_CharacterInfo->GetUpdateSpeed().ix() > 840)
	{
		m_WallCollision = Dir::RIGHT;
		if (m_CharacterInfo->GetDir().x != -1.f)
		{
			m_CharacterInfo->StopX();
		}
	}

	if (Up + m_CharacterInfo->GetUpdateSpeed().iy() < 120)
	{
		m_WallCollision = Dir::UP;
		if (m_CharacterInfo->GetDir().y != 1.f)
		{
			m_CharacterInfo->StopY();
		}

	}
	if (Down + m_CharacterInfo->GetUpdateSpeed().iy() > 410)
	{
		m_WallCollision = Dir::DOWN;
		if (m_CharacterInfo->GetDir().y != -1.f)
		{
			m_CharacterInfo->StopY();
		}

	}
}

void FlyBoss::MoveStart()
{
}

void FlyBoss::MoveStay()
{

	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"Idle");
		m_RenderHitLayer->ChangeAnimation(L"Idle");
	}
	//플레이어와 씬이 다르면 플레이하는 상태가 아니다.
	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}

	if (GetCharacterInfo()->GetAttackDelay() > GetCharacterInfo()->GetAttackDelayMax())
	{
		GetMonsterFSM()->ChangeState(L"Attack");
	}
	GetCharacterInfo()->SetAttackDelay(GetCharacterInfo()->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());


}

void FlyBoss::AttackStart()
{
	m_RenderBody->ChangeAnimation(L"Attack_Start");
	m_RenderHitLayer->ChangeAnimation(L"Attack_Start");

}

void FlyBoss::AttackStay()
{
	if (m_RenderBody->IsEndAni())
	{
		m_RenderBody->ChangeAnimation(L"Attack_End");
		m_RenderHitLayer->ChangeAnimation(L"Attack_End");
		m_MonsterFSM.ChangeState(L"Move");
		if (m_AllFly.size()>4)
		{
			std::list<Fly*>::iterator iter = m_AllFly.begin();
			std::list<Fly*>::iterator iterEnd = m_AllFly.end();
			for (; iter != iterEnd; ++iter)
			{
				(*iter)->TargetOut();
			}
			m_AllFly.clear();
			GetCharacterInfo()->SetAttackDelay(0.f);
			EngineSound::Play(L"Boss_Bug_Hiss.mp3", false, 0);
		}
		else
		{
			Fly* Actor = GetScene()->CreateActor<Fly>();
			Actor->SetPosition(GetPosition());
			Actor->SetRoomInfo(GetRoomInfo());
			m_RoomInfo->PushEnemy(Actor);
			Actor->On();
			Actor->BossTarget(this);
			GetCharacterInfo()->SetAttackDelay(0.f);
			m_AllFly.push_back(Actor);
			EngineSound::Play(L"Boss_Lite_Roar.mp3", false, 0);
		}
	}
}

void FlyBoss::AttackEnd()
{
}

void FlyBoss::DieStart()
{
	Enemy::DieStart();
}

void FlyBoss::DieStay()
{
	EngineSound::Stop(L"BossBGM.mp3");
	EngineSound::Play(L"BossKill.mp3", false, 0);
	Death();
}

void FlyBoss::DieEnd()
{
}

void FlyBoss::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 1);
		m_RenderHitLayer->RenderOn();
	}
	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_CharacterInfo->SetHP(m_CharacterInfo->GetHP() - 3);
		m_RenderHitLayer->RenderOn();
	}

	if (m_CharacterInfo->GetHP() <= 0.f)
	{
		m_MonsterFSM.ChangeState(L"Die");
	}
}

void FlyBoss::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void FlyBoss::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
