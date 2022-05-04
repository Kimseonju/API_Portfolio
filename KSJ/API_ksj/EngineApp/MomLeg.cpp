#include "MomLeg.h"
#include "LogicValue.h"
#include <EngineWindowResMgr.h>
#include <EngineCollision.h>
#include "Fly.h"
#include "RoomInfo.h"
#include "Player.h"
#include "EnemyTear.h"
#include "Core.h"
#include "Door.h"
#include <EngineRendererBasic.h>
#include "MOMBoss.h"
//static
//static func


MomLeg::MomLeg():
	m_Leg(nullptr)
	,m_Collision(nullptr)
	, m_MOMBoss(nullptr)
	,m_Time(0.f)
	, m_Attack(false)
	, m_AttackTimer(0.f)
	, m_Shadow(nullptr)
	, m_AttackPlay(false)
	, m_CollisionBody(nullptr)
	, m_RenderTimer(0.f)
	, m_RenderUpdate(false)
	, m_RenderUpdateCheck(false)
	, m_RenderPattern(0)
	, m_OldPivot(float4::ZERO)
	, m_bAttackSound(false)
	, m_bAttackInSound(false)
	, m_AttackSoundCount(0)
	, m_LegHitLayer(nullptr)
{
}

MomLeg::~MomLeg()
{
}

void MomLeg::Start()
{
	Enemy::Start();
	SetClassType(L"Mom");
	m_Leg = CreateRenderer<EngineRendererBasic>(500);
	m_Leg->TransCut_Setting(L"MomLeg.bmp", 0);
	m_Leg->SetPivotPos({ 50,-1000 });

	m_LegHitLayer=CreateRenderer<EngineRendererBasic>(500);
	m_LegHitLayer->TransCut_Setting(L"MomLegHit.bmp", 0);
	m_LegHitLayer->SetPivotPos({ 50,-1000 });
	m_LegHitLayer->SetAlpha(150);
	m_LegHitLayer->RenderOff();

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Bomb));
	m_Collision->AddStartEvent(this, &MomLeg::StartCol);
	m_Collision->AddStayEvent(this, &MomLeg::StayCol);
	m_Collision->SetScale({ 120, 100 });
	m_Collision->AddEndEvent(this, &MomLeg::EndCol);
	m_Collision->Off();

	m_CollisionBody = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
	m_CollisionBody->AddStartEvent(this, &MomLeg::BodyStartCol);
	m_CollisionBody->AddStayEvent(this, &MomLeg::BodyStayCol);
	m_CollisionBody->SetScale({ 120, 100 });
	m_CollisionBody->AddEndEvent(this, &MomLeg::BodyEndCol);
	m_CollisionBody->Off();

	m_Shadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
	m_Shadow->TransCut_Setting(L"shadow.bmp", 0);
	m_Shadow->SetRenderScale({ 180, 80 });
	m_Shadow->SetPivotPos({ 0.f, 30.f });
	m_Shadow->SetAlpha(100);
}


void MomLeg::Update()
{
	Enemy::Update();
	m_LegHitLayer->SetPivotPos(m_Leg->GetPivotPos());
	m_LegHitLayer->SetRenderScale(m_Leg->GetRenderScale());
}

void MomLeg::MoveRenderUpdate(const float4& num)
{
	m_OldPivot = num;
	if (m_RenderUpdate)
	{
		if (!m_RenderUpdateCheck)
		{
			m_RenderTimer = 0.f;
		}
		m_RenderTimer += EngineTimer::MainTimer.GetFDeltaTime();
		m_RenderUpdateCheck = true;
		if (m_RenderTimer > 0.1f && m_RenderTimer < 0.2f)
		{
			m_Leg->SetRenderScale({ 527,544 });
			float4 Pos = m_OldPivot;
			Pos.y = Pos.y + 80;
			m_Leg->SetPivotPos(Pos);
		}
		else if (m_RenderTimer >= 0.2f && m_RenderTimer < 0.3f)
		{

			m_Leg->SetRenderScale({ 327,844 });
			float4 Pos = m_OldPivot;
			Pos.y = Pos.y-60;
			m_Leg->SetPivotPos(Pos);
		}

		else if (m_RenderTimer >= 0.3f && m_RenderTimer < 0.4f)
		{
			m_Leg->SetRenderScale({ 427,694 });
			float4 Pos = m_OldPivot;
			m_Leg->SetPivotPos(Pos);
			m_RenderUpdate = false;
		}
		
	}
	
}

void MomLeg::AllHitRenderOn()
{
	m_LegHitLayer->RenderOn();
}

void MomLeg::AllHitRenderOff()
{
	m_LegHitLayer->RenderOff();
}


void MomLeg::Init(MOMBoss* _ParentActor)
{
	SetParentBase(_ParentActor);
	m_MOMBoss = _ParentActor;
}

