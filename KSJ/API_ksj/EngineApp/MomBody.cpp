#include "MomBody.h"
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


//적헤더
#include "Fly.h"
#include "Pooter.h"
#include "Boomfly.h"
#include "full_fly.h"
#include "Deathshead.h"
#include "Nerveending.h"
#include "Psychicmaw.h"
#include "Psychic_horf.h"
#include "Onetooth.h"
#include "Redboomfly.h"
#include "Horf.h"
#include "Dinga.h"
#include "Dip.h"
#include "Host.h"
#include "Moms_hand.h"
#include "Redmaw.h"
#include "Squirt.h"
#include "Sucker.h"
#include "Turret.h"


//static
LogicValue::EnemyType MomBody::MonsterCount= LogicValue::EnemyType::Fly;

//static func


void MomBody::MonsterCountNext()
{
	int temp = static_cast<int>(MonsterCount);
	temp++;
	if (static_cast<int>(LogicValue::EnemyType::MAX) == temp)
	{
		temp = 0;
	}
	MonsterCount = (LogicValue::EnemyType)temp;
}

MomBody::MomBody()
	: m_Door(nullptr)
	, m_Render_MomEye(nullptr)
	, m_Render_MomBody(nullptr)
	, m_Render_MomHand(nullptr)
	, m_Collision(nullptr)
	, m_HandTimer(0.f)
	, m_MOMBoss(nullptr)
	, m_Time(0.f)
	, m_Dir(float4::ZERO)
	, m_Hand(false)
	, m_MonsterRecall(false)
	, m_Body(nullptr)
	, m_BodyTimer(0.f)
	, m_CollisionResearch(nullptr)
	, m_Eye(nullptr)
	, m_EyeTimer(0.f)
	, m_Pattern(0)
	, m_RenderPattern(0)
	, m_RenderTimer(0.f)
	, m_Render_MomEyeLayerHit(nullptr)
	, m_Render_MomBodyLayerHit(nullptr)
	, m_Render_MomHandLayerHit(nullptr)
{
}

MomBody::~MomBody() 
{
}

void MomBody::Start()
{
	Enemy::Start();
	SetClassType(L"Mom");
	m_Door = GetScene()->CreateActor<Door>();
	
	m_Render_MomEye = CreateRenderer<EngineRendererBasic>(500);
	m_Render_MomBody = CreateRenderer<EngineRendererBasic>(500);
	m_Render_MomHand = CreateRenderer<EngineRendererAnim>(500);
	
	

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Enemy));
	m_Collision->AddStartEvent(this, &MomBody::StartCol);
	m_Collision->AddStayEvent(this, &MomBody::StayCol);
	m_Collision->AddEndEvent(this, &MomBody::EndCol);


	m_CollisionResearch = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::research));
	m_CollisionResearch->AddStartEvent(this, &MomBody::ResearchStartCol);
	m_CollisionResearch->AddStayEvent(this, &MomBody::ResearchStayCol);
	m_CollisionResearch->AddEndEvent(this, &MomBody::ResearchEndCol);

	m_Render_MomEye->Off();
	m_Render_MomBody->Off();
	m_Collision->Off();
	
}


void MomBody::Update()
{
	Enemy::Update();

	//m_Door->BossOpen();
	//손은 바로 후려친다.

	if (m_Hand)
	{
		m_HandTimer += EngineTimer::MainTimer.GetFDeltaTime();
		if (m_Pattern == 0)
		{
			m_Door->SetOpen(true);
			m_Pattern++;
			m_Collision->On();
			float4 scale = { 130.f,130.f };
			m_Collision->SetPivotPos(m_Dir * 70.f);
			m_Collision->SetScale({ scale });
			m_HandTimer = 0.f;
		}

		if (m_Pattern == 1)
		{
			if (m_HandTimer >= 2.f)
			{
				m_Collision->Off();
				m_Render_MomHand->ChangeAnimation(L"Back");
				m_Render_MomHandLayerHit->ChangeAnimation(L"Back");
				m_Door->SetOpen(false);
				m_HandTimer -= 2.f;
				m_Pattern++;
			}
		}
		
		if (m_HandTimer >= 2.f)
		{
			m_Collision->Off();
			m_HandTimer = -2.f;
			m_Hand = false;
			m_Pattern = 0;
		}
	}

	else if (m_Body && !m_Hand)
	{
		m_BodyTimer += EngineTimer::MainTimer.GetFDeltaTime();
		m_Collision->On();
		m_Render_MomBody->On();
		float4 scale = { 100.f,100.f };
		m_Collision->SetPivotPos(m_Dir * 10.f);
		m_Collision->SetScale({ scale });
		if (m_Pattern == 0)
		{
			m_Door->SetOpen(true);
			m_Pattern++;
		}
		
		if (m_Pattern == 1)
		{
			if (m_BodyTimer >= 0.5f)
			{
				if (m_MonsterRecall)
				{
					m_MonsterRecall = false;
					Enemy* Actor = nullptr;
					switch (MonsterCount)
					{
					case LogicValue::EnemyType::Fly:
						Actor = GetScene()->CreateActor<Fly>();
						break;
					case LogicValue::EnemyType::Pooter:
						Actor = GetScene()->CreateActor<Pooter>();
						break;
					case LogicValue::EnemyType::full_fly:
						Actor = GetScene()->CreateActor<full_fly>();
						break;
					case LogicValue::EnemyType::Nerveending:
						Actor = GetScene()->CreateActor<Nerveending>();
						break;
					case LogicValue::EnemyType::Psychic_horf:
						Actor = GetScene()->CreateActor<Psychic_horf>();
						break;
					case LogicValue::EnemyType::Onetooth:
						Actor = GetScene()->CreateActor<Onetooth>();
						break;
					case LogicValue::EnemyType::Horf:
						Actor = GetScene()->CreateActor<Horf>();
						break;
					case LogicValue::EnemyType::Host:
						Actor = GetScene()->CreateActor<Host>();
						break;
					case LogicValue::EnemyType::Redmaw:
						Actor = GetScene()->CreateActor<Redmaw>();
						break;
					case LogicValue::EnemyType::Sucker:
						Actor = GetScene()->CreateActor<Sucker>();
						break;
					case LogicValue::EnemyType::MAX:
						break;
					default:
						break;
					}
					MonsterCountNext();
					if (Actor == nullptr)
					{
						EngineDebug::AssertMsg("if (Actor == nullptr)");
					}
					Actor->On();
					m_RoomInfo->PushFinshBossEnemy(Actor);
					Actor->SetRoomInfo(GetRoomInfo());
					float4 a = GetPosition();
					Actor->SetPosition(GetPosition() + (m_Dir * 100.f));
					EngineSound::Play(L"summon.mp3", false, 0);
				}
				m_Pattern++;
				m_BodyTimer -= 0.5f;
			}
		}
		
		if (m_Pattern == 2)
		{
			if (m_BodyTimer >= 1.f)
			{
				m_Door->SetOpen(false);
				m_BodyTimer -= 1.f;
				m_Pattern++;
			}
		}
		
		if (m_Pattern == 3)
		{
			if (m_BodyTimer >= 0.3f)
			{
				m_Collision->Off();
				m_Render_MomBody->Off();
				m_BodyTimer -= 0.3f;
				m_Body = false;
				m_Pattern = 0;
			}

		}
		

	}

	else if (m_Eye && !m_Hand)
	{
		m_EyeTimer += EngineTimer::MainTimer.GetFDeltaTime();
		m_Collision->On();
		m_Render_MomEye->On();
		float4 scale = { 100.f,100.f };
		m_Collision->SetPivotPos(m_Dir * 10.f);
		m_Collision->SetScale({ scale });


		if (m_Pattern == 0)
		{
			m_Door->SetOpen(true);
			m_Pattern++;
		}

		if (m_Pattern == 1)
		{
			if (m_EyeTimer >= 0.5f)
			{

				m_Pattern++;
			}
		}

		if (m_Pattern == 2)
		{
			if (m_EyeTimer >= 1.f)
			{
				m_Door->SetOpen(false);
				m_EyeTimer = 0.f;
				m_Pattern++;
			}
		}

		if (m_Pattern == 3)
		{
			if (m_EyeTimer >= 0.3f)
			{
				m_Collision->Off();
				m_Render_MomEye->Off();
				m_EyeTimer = 0.f;
				m_Eye = false;
				m_Pattern = 0;
			}

		}
	}
}

void MomBody::UpdateNext()
{
}

void MomBody::Die()
{
	if(nullptr != m_Door)
		m_Door->Death();

	if(nullptr!=m_Render_MomEye)
		m_Render_MomEye->Death();


	if (nullptr != m_Render_MomBody)
		m_Render_MomBody->Death();

	if (nullptr != m_Render_MomHand)
		m_Render_MomHand->Death();

	if (nullptr != m_Render_MomEyeLayerHit)
		m_Render_MomEyeLayerHit->Death();

	if (nullptr != m_Render_MomBodyLayerHit)
		m_Render_MomBodyLayerHit->Death();

	if (nullptr != m_Render_MomHandLayerHit)
		m_Render_MomHandLayerHit->Death();

	if (nullptr != m_Collision)
		m_Collision->Death();

	if (nullptr != m_CollisionResearch)
		m_CollisionResearch->Death();
}

void MomBody::MoveRender()
{

}







void MomBody::Init(const EngineString& _Dir, const float4& dir, MOMBoss* _ParentActor)
{
	m_Door->SetDoorImage(static_cast<int>(LogicValue::RoomType::FinalBoss), dir);
	SetPosition({ 410 * dir.ix(), 200 * dir.iy() });
	SetParentBase(_ParentActor);
	m_Door->SetParentBase(this);
	m_Door->SetOpen(false);
	SetRoomInfo(_ParentActor->GetRoomInfo());
	//반대방향 저장하기
	m_Dir = -dir;

	m_MOMBoss = _ParentActor;
	{
		EngineString str = L"MomBody";
		str += _Dir;

		EngineString strLayer = str;
		strLayer += L"Hit.bmp";


		m_Render_MomEyeLayerHit = CreateRenderer<EngineRendererBasic>(500);
		m_Render_MomBodyLayerHit = CreateRenderer<EngineRendererBasic>(500);


		m_Render_MomEyeLayerHit->TransCut_Setting(strLayer, 0);
		m_Render_MomEyeLayerHit->SetRenderScale({ 128, 128 });
		m_Render_MomEyeLayerHit->SetPivotPos(m_Dir * 30.f);
		//1,2 는 바디
		m_Render_MomBodyLayerHit->TransCut_Setting(strLayer, 1);
		m_Render_MomBodyLayerHit->SetRenderScale({ 128, 128 });
		m_Render_MomBodyLayerHit->SetPivotPos(m_Dir * 50.f);
		m_Render_MomEyeLayerHit->SetAlpha(150);
		m_Render_MomBodyLayerHit->SetAlpha(150);
		m_Render_MomEyeLayerHit->RenderOff();
		m_Render_MomBodyLayerHit->RenderOff();
		m_Render_MomEyeLayerHit->Off();
		m_Render_MomBodyLayerHit->Off();

		str += L".bmp";
		//0은 눈
		m_Render_MomEye->TransCut_Setting(str, 0);
		m_Render_MomEye->SetRenderScale({ 128, 128 });
		m_Render_MomEye->SetPivotPos(m_Dir * 30.f);
		//1,2 는 바디
		m_Render_MomBody->TransCut_Setting(str, 1);
		m_Render_MomBody->SetRenderScale({ 128, 128 });
		m_Render_MomBody->SetPivotPos(m_Dir * 50.f);
	}
	{
		EngineString str = L"MomHand";
		str += _Dir;
		EngineString strLayer = str;
		strLayer += L"Hit.bmp";

		m_Render_MomHandLayerHit = CreateRenderer<EngineRendererAnim>(500);
		m_Render_MomHandLayerHit->SetRenderScale({ 512, 512 });
		m_Render_MomHandLayerHit->CreateAnimation(L"Attack", strLayer, 0, 2, 0.1f, false);
		m_Render_MomHandLayerHit->CreateAnimation(L"Back", strLayer, 0, 2, 0.1f, false, true);
		m_Render_MomHandLayerHit->CreateAnimation(L"Idle", strLayer, 0, 0, 0.1f, false);
		m_Render_MomHandLayerHit->ChangeAnimation(L"Idle");
		m_Render_MomHandLayerHit->RenderOff();
		m_Render_MomHandLayerHit->SetAlpha(150);

		str += L".bmp";
		//0은 눈
		m_Render_MomHand->SetRenderScale({ 512, 512 });
		m_Render_MomHand->CreateAnimation(L"Attack", str, 0, 2, 0.1f, false);
		m_Render_MomHand->CreateAnimation(L"Back", str, 0, 2, 0.1f, false, true);
		m_Render_MomHand->CreateAnimation(L"Idle", str, 0, 0, 0.1f, false);
		m_Render_MomHand->ChangeAnimation(L"Idle");
	}

	{
		//임시스케일

		m_Collision->SetScale({ 100.f,100.f});
		m_CollisionResearch->SetScale({ 200.f,200.f });
		
	}


}

void MomBody::AllHitRenderOn()
{
	m_Render_MomEyeLayerHit->RenderOn();
	m_Render_MomBodyLayerHit->RenderOn();
	m_Render_MomHandLayerHit->RenderOn();
}

void MomBody::AllHitRenderOff()
{
	m_Render_MomEyeLayerHit->RenderOff();
	m_Render_MomBodyLayerHit->RenderOff();
	m_Render_MomHandLayerHit->RenderOff();
}