#include "Bomb.h"

#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include "BombEffect.h"
#include <EngineScene.h>
#include "LogicValue.h"
#include "Core.h"
#include "Player.h"
#include "RoomInfo.h"

// Static Var
// Static Func

// member Var
Bomb::Bomb() : m_RenderBody(nullptr), m_Count(0.f), m_CountMax(3.0f), m_Range(100.f), m_Speed(0.f), m_RenderLayer(nullptr)
, num(0), m_ChangeCount(0.f), m_Collision(nullptr), m_bCheckPlayer(false), m_WallCollision(Dir::MAX), m_CharacterInfo(nullptr)
, m_RoomInfo(nullptr)
, m_CollisionPlayer(nullptr)
{

}

Bomb::~Bomb()
{
	if(m_CharacterInfo)
		delete m_CharacterInfo;
	m_CharacterInfo = nullptr;
}
// member Func

void Bomb::Start()
{
	SetSize({ 34.f,34.f });
	SetClassType(L"Bomb");
	m_CharacterInfo = new CCharacterInfo();

	m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderBody->CreateAnimation(L"bombs", L"bombs.bmp", 22, 24);
	m_RenderBody->ChangeAnimation(L"bombs");


	m_RenderLayer = CreateRenderer<EngineRendererAnim>(500);
	m_RenderLayer->SetRenderScale({ 64, 64 });
	m_RenderLayer->CreateAnimation(L"StartBomb", L"bombLayer.bmp", 0, 3, 0.2f, true);
	m_RenderLayer->CreateAnimation(L"Bomb", L"bombLayer.bmp", 0, 2, 0.05f);
	m_RenderLayer->ChangeAnimation(L"StartBomb");
	m_RenderLayer->SetAlpha(128);

	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::MapObject));
	m_Collision->SetScale({ GetSize() });
	m_Collision->AddStartEvent(this, &Bomb::StartCol);
	m_Collision->AddStayEvent(this, &Bomb::StayCol);
	m_Collision->AddEndEvent(this, &Bomb::EndCol);

	m_CollisionPlayer = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::MapObject));
	m_CollisionPlayer->SetScale({ GetSize()+15.f });
	m_CollisionPlayer->AddStartEvent(this, &Bomb::PlayerStartCol);
	m_CollisionPlayer->AddStayEvent(this, &Bomb::PlayerStayCol);
	m_CollisionPlayer->AddEndEvent(this, &Bomb::PlayerEndCol);
}
void Bomb::Update()
{
	if (nullptr == LogicValue::MainPlayer)
	{
		return;
	}

	if (LogicValue::MainPlayer->GetScene() != Core::SceneManager.GetCurScene())
	{
		return;
	}

	m_CharacterInfo->SetDir(float4::ZERO);

	m_Count += EngineTimer::MainTimer.GetFDeltaTime();
	if (m_Count >= 1.5f)
	{
		m_ChangeCount += EngineTimer::MainTimer.GetFDeltaTime();
		m_RenderLayer->ChangeAnimation(L"Bomb");
		if (num % 2 == 0)
		{
			m_RenderBody->SetRenderScale({ 64, 64 });
			m_RenderLayer->SetRenderScale({ 64, 64 });
			m_RenderBody->SetPivotPos({ 0.f,0.f });
			m_RenderLayer->SetPivotPos({ 0.f,0.f });
		}
		else
		{
			m_RenderBody->SetRenderScale({ 84, 44 });
			m_RenderLayer->SetRenderScale({ 84, 44 });
			m_RenderBody->SetPivotPos({ 0.f,10.f });
			m_RenderLayer->SetPivotPos({ 0.f,10.f });
		}
		if (m_ChangeCount > 0.1f)
		{
			m_ChangeCount = 0;
			++num;
		}
	}
	if (m_Count > m_CountMax)
	{
		//Æø¹ßÀÌº¥Æ®
		
		EngineSound::Play(L"explosion.mp3", false,0);
		BombEffect* bombeffect = GetScene()->CreateActor<BombEffect>();
		bombeffect->SetPosition(GetPosition());
		if (m_RoomInfo)
		{
			m_RoomInfo->PushActor(bombeffect);
			
		}
		this->Death();
	}

	m_CharacterInfo->Update();
	MapCollider();
	MovePosition(m_CharacterInfo->GetUpdateSpeed());
}

void Bomb::DebugRender()
{
}

void Bomb::OffTask()
{
	m_Count = 0.f;
	m_RenderBody->SetRenderScale({ 64, 64 });
	m_RenderLayer->SetRenderScale({ 64, 64 });
}

void Bomb::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 5.f);
	}
}

void Bomb::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
	
}

void Bomb::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player))
	{
		if (!m_bCheckPlayer)
		{
			return;
		}
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 1.f);
	}

	

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::MapObject))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 1.f);
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::BombObject))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 1.f);
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 1.f);
	}
}
void Bomb::PlayerStartCol(EngineCollision* _This, EngineCollision* _Other)
{



}
void Bomb::PlayerEndCol(EngineCollision* _This, EngineCollision* _Other)
{
	m_bCheckPlayer = true;
	m_CollisionPlayer->Off();
}
void Bomb::PlayerStayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
void Bomb::MapCollider()
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
			m_CharacterInfo->StopX();
	}
	if (Right + m_CharacterInfo->GetUpdateSpeed().ix() > 850)
	{
		m_WallCollision = Dir::RIGHT;
		if (m_CharacterInfo->GetDir().x != -1.f)
			m_CharacterInfo->StopX();
	}

	if (Up + m_CharacterInfo->GetUpdateSpeed().iy() < 101)
	{
		m_WallCollision = Dir::UP;
		if (m_CharacterInfo->GetDir().y != 1.f)
			m_CharacterInfo->StopY();
	}
	if (Down + m_CharacterInfo->GetUpdateSpeed().iy() > 435)
	{
		m_WallCollision = Dir::DOWN;
		if (m_CharacterInfo->GetDir().y != -1.f)
			m_CharacterInfo->StopY();
	}
}
