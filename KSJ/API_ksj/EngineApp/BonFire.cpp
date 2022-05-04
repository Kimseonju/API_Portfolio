#include "BonFire.h"

#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include "PoofEffect.h"

// Static Var
// Static Func

// member Var
BonFire::BonFire() : RenderBody(nullptr), RenderHead(nullptr), m_FireHP(5.f), m_FireHPMax(5.f), m_Collision(nullptr)
, m_Die(false)

{
}

BonFire::~BonFire()
{

}
// member Func

void BonFire::Start()
{
	SetSize({ 32.f,40.f });
	SetClassType(L"BonFire");

	RenderBody = CreateRenderer<EngineRendererAnim>(6);
	RenderBody->SetRenderScale({ 64, 64 });
	RenderBody->CreateAnimation(L"FireOn", L"FireAni_down.bmp", 0, 2);
	RenderBody->CreateAnimation(L"FireOff", L"FireAni_down.bmp", 3, 3);

	RenderHead = CreateRenderer<EngineRendererAnim>(500);
	RenderHead->SetRenderScale({ 96, 96 });
	RenderHead->CreateAnimation(L"FireOn", L"fireAni_up.bmp", 0, 5);
	RenderHead->SetPivotPos({2.f,-36.f + (m_FireHPMax - m_FireHP) * 2.f });

	RenderBody->ChangeAnimation(L"FireOn");
	RenderHead->ChangeAnimation(L"FireOn");


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::MapObject));
	m_Collision->SetScale({ GetSize() });
	m_Collision->AddStartEvent(this, &BonFire::StartCol);
	m_Collision->AddStayEvent(this, &BonFire::StayCol);
	m_Collision->AddEndEvent(this, &BonFire::EndCol);

}
void BonFire::Update()
{
	RenderHead->SetPivotPos({ 2.f,-36.f + (m_FireHPMax - m_FireHP) * 7.f });
	float4 scale = { 96.f,96.f };
	scale = scale - (m_FireHPMax - m_FireHP) * 14.f;
	RenderHead->SetRenderScale({scale});

	if (m_FireHP <= 0.f)
	{
		//�浹����
		m_Collision->Off();
		//�Ҳ���
		RenderHead->Off();
		RenderBody->ChangeAnimation(L"FireOff");
		//��������Ȯ����.. ���߿�
		if (!m_Die)
		{
			m_Die = true;

			PoofEffect* actor = GetScene()->CreateActor< PoofEffect>();
			actor->SetPosition(GetPosition());
			actor->FireObject();
			EngineSound::Stop(L"fireBurning.mp3");
			EngineSound::Play(L"steam.mp3", false, 0);
		}
	}
	else
	{
		EngineSound::Play(L"fireBurning.mp3", true, 0);
	}
}
void BonFire::DebugRender()
{
}
void BonFire::OffTask()
{
	EngineSound::Stop(L"fireBurning.mp3");
}
void BonFire::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
	//HP 3���κο� �������������� 1�� �޸鼭 �̹��� �۾���
	//0�̵Ǹ� ��������Ʈ����, ������ �ݸ��� ����
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::EnemyTear)||
		_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::PlayerTear ))
	{
		m_FireHP--;
	}
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		m_FireHP=0;
	}
}

void BonFire::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void BonFire::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
