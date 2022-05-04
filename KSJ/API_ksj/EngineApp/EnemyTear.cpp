#include "EnemyTear.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include "Player.h"
#include "PlayScene.h"
#include "RoomInfo.h"
//static
//static func


EnemyTear::EnemyTear() :
	m_RenderBody(nullptr), m_Shadow(nullptr), m_Dir(float4::ZERO),
	m_ShotSpeed(100.f), m_ShotRange(150), m_MoveRange(0.f), m_Att(100.f),
	m_GravityForce(150.f), m_Gravity(false), m_Time(0.f), m_Col(nullptr), m_MoveCount(0)
	, m_bGuided(false), m_SoundMoveEnd(true), m_Drop(false)
{
}

EnemyTear::~EnemyTear()
{
}

void EnemyTear::Start()
{
	SetClassType(L"EnemyTear");
	SetSize({ 16.f,16.f });

	m_RenderBody = CreateRenderer<EngineRendererAnim>(static_cast<int>(LogicValue::RenderGroup::Tear));
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->CreateAnimation(L"Idle", L"EnemyTear.bmp", 0, 0);
	m_RenderBody->CreateAnimation(L"Die", L"EnemyTear.bmp", 1, 15, 0.05f, false, false);
	m_RenderBody->ChangeAnimation(L"Idle");

	m_Col = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::EnemyTear));
	m_Col->SetScale({ GetSize() });
	m_Col->AddStartEvent(this, &EnemyTear::StartCol);
	m_Col->AddStayEvent(this, &EnemyTear::StayCol);
	m_Col->AddEndEvent(this, &EnemyTear::EndCol);


	m_Shadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
	m_Shadow->TransCut_Setting(L"shadow.bmp", 0);
	m_Shadow->SetRenderScale({ 20, 10 });
	m_Shadow->SetPivotPos({ 0, 30 });
	m_Shadow->SetAlpha(100);


	EnemyTearsFsm.CreateState(L"MoveStay", this, &EnemyTear::MoveStay);
	EnemyTearsFsm.CreateState(L"MoveEnd", this, &EnemyTear::MoveEnd);
}

void EnemyTear::Update()
{
	m_Col->SetPivotPos({ 0.f, m_RenderBody->GetPivotPos().y });
	EnemyTearsFsm.Update();
}

void EnemyTear::DebugRender()
{
}

void EnemyTear::PlayFire(EngineActor* _Actor, const float4& _Dir, const float4& _PivotPos,
	const float4& _Pos, const float& _Att, const float& _ShotSpeed, const float& _ShotRange, bool _bGuided)
{
	FireMonster = _Actor->GetClassType();
	m_Dir = _Dir;
	m_Col->SetPivotPos({ _PivotPos.x, _PivotPos.y });
	int Mapx = _Pos.ix() / 960;
	int Mapy = _Pos.iy() / 540;
	RoomInfo* room=LogicValue::MainScene->GetMap(Mapx, Mapy);
	room->PushTear(this);
	SetPosition(_Pos);
	m_Att = _Att;
	m_ShotSpeed = _ShotSpeed * 300;
	//둘다임시값 속도에따라 Range 계산하기 또는 시간으로계산
	m_ShotRange = 150;
	m_bGuided = _bGuided;
	EnemyTearsFsm.ChangeState(L"MoveStay");


	if (_bGuided)
	{
		//이미지 변경
	}

}

void EnemyTear::MapCollider()
{

}

void EnemyTear::MoveStay()
{
	//Body를 아래로
	m_Time += EngineTimer::MainTimer.GetFDeltaTime();
	float4 movePos = m_Dir;

	if (m_bGuided)
	{
		float4 pos = LogicValue::MainPlayer->GetPosition()- GetPosition();

		float Angle = float4::GetAngle(movePos);
		float NewAngle = float4::GetAngle(pos);;

		float temp = NewAngle - Angle;
		if (abs(temp) > 180.f)
		{
			if (NewAngle <= Angle)
			{
				Angle += EngineTimer::MainTimer.GetFDeltaTime() * 180.f;
			}
			else
			{
				Angle -= EngineTimer::MainTimer.GetFDeltaTime() * 180.f;
			}
		}
		else
		{
			if (NewAngle >= Angle)
			{
				Angle += EngineTimer::MainTimer.GetFDeltaTime() * 180.f;
			}
			else
			{
				Angle -= EngineTimer::MainTimer.GetFDeltaTime() * 180.f;
			}
		}


		if (Angle >= 360.f)
			Angle = 0.f;
		else if (Angle <= 0.f)
			Angle = 360.f;
		movePos = float4::AngleToDir2DDeg(Angle);
	}
	m_Dir = movePos;
	movePos = movePos * EngineTimer::FDeltaTime(m_ShotSpeed);

	float4 _CurPos=float4::ZERO;

	if (m_MoveCount == 0)
	{
		if (m_Time > 1.f)
		{
			_CurPos = float4::Lerp2DMax(0, 10, m_Time);
			m_MoveCount++;
			m_Time = 0.f;
			return;
		}
		_CurPos = float4::Lerp2DMax(0, 10, m_Time);
		_CurPos.x = 0.f;
	}
	else if (m_MoveCount == 1)
	{
		if (m_Time > 0.3f)
		{
			_CurPos = float4::Lerp2DMax(10, 60, m_Time);
			m_MoveCount++;
			return;
		}
		_CurPos = float4::Lerp2DMax(10, 60, m_Time);
		_CurPos.x = 0.f;
	}
	else
	{
		m_Drop = true;
		EnemyTearsFsm.ChangeState(L"MoveEnd");
		return;
	}


	m_RenderBody->SetPivotPos(_CurPos);
	MovePosition(movePos);
}

void EnemyTear::MoveEnd()
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
		Death();
	}
}


void EnemyTear::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	EnemyTearsFsm.ChangeState(L"MoveEnd");
}

void EnemyTear::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void EnemyTear::StayCol(EngineCollision* _This, EngineCollision* _Other)
{

}
