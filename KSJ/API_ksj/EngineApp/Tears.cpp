#include "Tears.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include <EngineRendererBasic.h>
#include <EngineCollision.h>
#include "LogicValue.h"
#include "PlayScene.h"
#include "RoomInfo.h"
#include "Enemy.h"
//static
//static func


Tears::Tears() :
	m_RenderBody(nullptr), m_Shadow(nullptr), m_Dir(float4::ZERO),
	m_ShotSpeed(100.f), m_ShotRange(150), m_MoveRange(0.f), m_Att(100.f),
	m_GravityForce(150.f), m_Gravity(false), m_Time(0.f), m_Col(nullptr), m_MoveCount(0),
	m_FSMDie(false), m_Drop(false), m_SoundMoveEnd(true)
	, m_CheckPos(float4::ZERO)
	, m_bGuided(false)
	, m_Room(nullptr)
	, m_Movepos(float4::ZERO)
{
}

Tears::~Tears()
{
}

void Tears::Start()
{

	SetClassType(L"Tear");
	SetSize({ 16.f,16.f });

	m_RenderBody = CreateRenderer<EngineRendererAnim>(static_cast<int>(LogicValue::RenderGroup::Tear));
	m_RenderBody->SetRenderScale({ 64, 64 });

	m_Col = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::PlayerTear));
	m_Col->SetScale({ GetSize() });
	m_Col->AddStartEvent(this, &Tears::StartCol);
	m_Col->AddStayEvent(this, &Tears::StayCol);
	m_Col->AddEndEvent(this, &Tears::EndCol);

	{
		m_Shadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
		m_Shadow->TransCut_Setting(L"shadow.bmp", 0);
		m_Shadow->SetRenderScale({ 20, 10 });
		m_Shadow->SetPivotPos({ 0, 30 });
		m_Shadow->SetAlpha(100);
	}



	//날라간다
	TearsFsm.CreateState(L"MoveStay", this, &Tears::MoveStay);
	//충돌, 떨어지기
	TearsFsm.CreateState(L"MoveEnd", this, &Tears::MoveEnd);
}

void Tears::Update()
{
	m_Col->SetPivotPos({ 0.f, m_RenderBody->GetPivotPos().y });
	TearsFsm.Update();

	MapCollider();

}

void Tears::DebugRender()
{
}

void Tears::PlayFire(EngineActor* _Actor, const float4& _Dir, const float4& _PivotPos,
	const float4& _Pos, const float& _Att, const float& _ShotSpeed, const float& _ShotRange
	, bool _bGuided)
{
	m_Dir = _Dir;
	SetPosition(_Pos);
	m_CheckPos = GetPosition();
	m_Att = _Att;
	m_ShotSpeed = _ShotSpeed;
	//둘다임시값 속도에따라 Range 계산하기 또는 시간으로계산
	m_ShotRange = _ShotRange;

	float4 Scale = m_RenderBody->GetRenderScale();
	float _Attscale = _Att / 10.f;
	m_RenderBody->SetRenderScale({ Scale * _Attscale });

	int Mapx = _Pos.ix() / 960;
	int Mapy = _Pos.iy() / 540;
	RoomInfo* room = LogicValue::MainScene->GetMap(Mapx, Mapy);
	room->PushTear(this);

	TearsFsm.ChangeState(L"MoveStay");
	m_bGuided = _bGuided;
	if (m_bGuided)
	{
		m_RenderBody->CreateAnimation(L"Idle", L"PlayerTear.bmp", 0, 0);
		m_RenderBody->CreateAnimation(L"Die", L"PlayerTear.bmp", 1, 15, 0.05f, false, false);
		m_RenderBody->ChangeAnimation(L"Idle");
	}
	else
	{
		m_RenderBody->CreateAnimation(L"Idle", L"PlayerTear.bmp", 0, 0);
		m_RenderBody->CreateAnimation(L"Die", L"PlayerTear.bmp", 1, 15, 0.05f, false, false);
		m_RenderBody->ChangeAnimation(L"Idle");
	}

}


void Tears::MapCollider()
{
	float4 pos = GetPosition();

	pos.x = static_cast<float>(pos.ix() % 960);
	pos.y = static_cast<float>(pos.iy() % 540);
	int Left = pos.ix() - GetSize().ihx();
	int Right = pos.ix() + GetSize().ihx();
	int Up = pos.iy() - GetSize().ihy();
	int Down = pos.iy() + GetSize().ihy();
	if (Left < 82)
	{
		m_FSMDie = true;
	}
	if (Right > 870)
	{
		m_FSMDie = true;
	}

	if (Up < 81)
	{
		m_FSMDie = true;
	}
	if (Down > 455)
	{

		m_FSMDie = true;
	}
}
///////////////////////////////충돌
void Tears::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	TearsFsm.ChangeState(L"MoveEnd");
	// 여기서 다 지워졌어야 하는데. 다 지워졌다.
	m_Col->Off();
}
void Tears::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void Tears::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
///////////////////////////////FSM
void Tears::MoveStay()
{
	//Body를 아래로
	m_Time += EngineTimer::MainTimer.GetFDeltaTime();
	float4 movePos = m_Dir;

	if (m_bGuided)
	{

		if (nullptr != m_Target)
		{
			float4 pos = m_Target->GetPosition() - GetPosition();
			pos.Normalize();

			float Angle = float4::GetAngle(movePos);
			float NewAngle = float4::GetAngle(pos);;
			float temp = NewAngle - Angle;
			if (abs(temp) > 180.f)
			{
				if (NewAngle <= Angle)
				{
					Angle += EngineTimer::MainTimer.GetFDeltaTime() * 360.f;
				}
				else
				{
					Angle -= EngineTimer::MainTimer.GetFDeltaTime() * 360.f;
				}
			}
			else
			{
				if (NewAngle >= Angle)
				{
					Angle += EngineTimer::MainTimer.GetFDeltaTime() * 360.f;
				}
				else
				{
					Angle -= EngineTimer::MainTimer.GetFDeltaTime() * 360.f;
				}
			}


			if (Angle >= 360.f)
				Angle = 0.f;
			else if (Angle <= 0.f)
				Angle = 360.f;
			movePos = float4::AngleToDir2DDeg(Angle);
		}
		else
		{
			if (nullptr != m_Room)
			{
				Enemy* Target = m_Room->TargetEnemyFind(this);
				m_Target = Target;
			}
		}
	}
	m_Dir = movePos;
	movePos = movePos * EngineTimer::FDeltaTime(m_ShotSpeed);

	float4 CurPos;

	if (m_FSMDie)
	{
		TearsFsm.ChangeState(L"MoveEnd");
		return;
	}


	if (m_MoveCount == 0)
	{
		CurPos = float4::Lerp2DMax(0, 10, m_Time);
		CurPos.x = 0.f;
		if (m_ShotRange < (m_Movepos.Len()))
		{

			m_Time = 0.f;
			m_MoveCount = 1;
		}

	}
	else if (m_MoveCount == 1)
	{
		if (m_Time > 0.3f)
		{
			CurPos = float4::Lerp2DMax(10, 60, m_Time);
			m_MoveCount++;
			return;
		}
		CurPos = float4::Lerp2DMax(10, 60, m_Time);
		CurPos.x = 0.f;
	}
	else
	{

		m_Drop = true;
		TearsFsm.ChangeState(L"MoveEnd");
		return;
	}


	m_RenderBody->SetPivotPos(CurPos);
	MovePosition(movePos);
	m_Movepos += movePos;
}

void Tears::MoveEnd()
{
	if (m_SoundMoveEnd)
	{
		if (m_Drop)
		{
			EngineSound::Play(L"TearDrop.mp3", false, 0);
		}
		else
		{
			EngineSound::Play(L"tearPop.mp3", false, 0);
		}
		m_SoundMoveEnd = false;
	}


	m_RenderBody->ChangeAnimation(L"Die");
	m_Shadow->Off();
	m_Col->Off();
	if (m_RenderBody->IsEndAni())
	{
		//Off();
		// 충돌 끝났다고 다른 애들한테 날린다......
		Death();
	}
}

void Tears::UpdateNext()
{
	if (nullptr != m_Target)
	{
		if (m_Target->IsDeath())
		{
			m_Target = nullptr;
		}
	}

}

