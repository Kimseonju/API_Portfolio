#include "Familiar.h"
#include <EngineRendererAnim.h>
#include <EngineCollision.h>
#include <EngineTimer.h>
#include "LogicValue.h"
#include <EngineRendererBasic.h>
//static
//static func


Familiar::Familiar() : m_RenderBody(nullptr), m_Target(nullptr), m_Angle(0.f)
, m_CharacterInfo(nullptr)
{
}

Familiar::~Familiar()
{
	if(m_CharacterInfo)
		delete m_CharacterInfo;
	m_CharacterInfo = nullptr;
}

void Familiar::Start()
{
	SetClassType(L"Familiar");
	m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
	m_RenderBody->SetRenderScale({ 64,64 });
	m_CharacterInfo = new CCharacterInfo();
	MovePosition({ 0,1 });
	//m_CharacterInfo->SetAttackDelayMax(2.5f);
	//m_RenderBody->CreateAnimation(L"DownFire", L"costume_drfetus.bmp", 0, 1, 0.2f, true, false);
	//m_RenderBody->CreateAnimation(L"RightFire", L"costume_drfetus.bmp", 2, 3, 0.2f, true, false);
	//m_RenderBody->CreateAnimation(L"LeftFire", L"costume_drfetus.bmp", 6, 7, 0.2f, true, false);
	//m_RenderBody->CreateAnimation(L"UpFire", L"costume_drfetus.bmp", 4, 5, 0.2f, true, false);
	//
	//m_RenderBody->CreateAnimation(L"DownIdle", L"costume_drfetus.bmp", 1, 1, 0.2f, true, false);
	//m_RenderBody->CreateAnimation(L"RightIdle", L"costume_drfetus.bmp", 3, 3, 0.2f, true, false);
	//m_RenderBody->CreateAnimation(L"LeftIdle", L"costume_drfetus.bmp", 7, 7, 0.2f, true, false);
	//m_RenderBody->CreateAnimation(L"UpIdle", L"costume_drfetus.bmp", 4, 4, 0.2f, true, false);

	EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::Shadow));
	NewShadow->TransCut_Setting(L"shadow.bmp", 0);
	NewShadow->SetRenderScale({ 24, 12 });
	NewShadow->SetPivotPos({ 0, 30 });
	NewShadow->SetAlpha(100);
}

void Familiar::Update()
{
	if (!m_Target)
	{
		EngineDebug::AssertMsg("if (!m_Target)");
	}
	//����Ÿ�̸� ��� ����
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::MainTimer.GetFDeltaTime());

	//�йи���� �йи�� ����ٴ� �� �Ÿ� ���ϱ�
	float4 Dir = m_Target->GetPosition() - GetPosition();
	// �Ÿ��� �ָ�
	if (50.f < float4::Len2D(Dir))
	{	//������ ���� �����̱�
		float Angle = float4::GetAngle(m_Target->GetPosition(), GetPosition());
		//
		//Dir.Normalize();
		m_CharacterInfo->AccelSpeedMove(Dir, 0.5f);
		AngleCheck(Angle);
	}

}

void Familiar::UpdateNext()
{
	m_CharacterInfo->Update();
	MovePosition(m_CharacterInfo->GetUpdateSpeed());
}

void Familiar::ChangeAnimationdir(const EngineString& _dir)
{
	//�Ӹ��� ���������� ���ݻ����϶��� �̰� ���ǰԲ� ���� �׿ܿ� angle�� Ȯ��
	//���߿� �׽�Ʈ�ϰ� ����
	m_RenderBody->ChangeAnimation(_dir);
}
void Familiar::FirstAnimationdir(const EngineString& _dir)
{
	m_RenderBody->FirstAnimation(_dir);
}
void Familiar::FirstAnimationclear()
{
	m_RenderBody->FirstAnimationClear();
}


void Familiar::AngleCheck(float Angle)
{//�����ʹ���
	if (Angle >= 315.f || Angle < 45.f)
	{
		ChangeAnimationdir(L"RightIdle");
	}
	//����
	else if (Angle >= 135.f && Angle < 225.f)
	{
		ChangeAnimationdir(L"LeftIdle");
	}
	//��

	else if (Angle >= 225.f && 315.f > Angle)
	{
		ChangeAnimationdir(L"UpIdle");
	}
	//�Ʒ�
	else if (Angle >= 45.f && 135.f > Angle) 
	{
		ChangeAnimationdir(L"DownIdle");
	}
}
