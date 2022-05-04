#include "Familiar_brotherbobby.h"
#include <EngineRendererAnim.h>
#include "Tears.h"
//static
//static func


Familiar_brotherbobby::Familiar_brotherbobby()
{
}

Familiar_brotherbobby::~Familiar_brotherbobby()
{
}

void Familiar_brotherbobby::Start()
{
	Familiar::Start();
	m_RenderBody->CreateAnimation(L"DownFire", L"familiar_brotherbobby.bmp", 0, 1, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"RightFire", L"familiar_brotherbobby.bmp", 2, 3, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"LeftFire", L"familiar_brotherbobby.bmp", 6, 7, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"UpFire", L"familiar_brotherbobby.bmp", 4, 5, 0.2f, true, false);
			
	m_RenderBody->CreateAnimation(L"DownIdle", L"familiar_brotherbobby.bmp", 0, 0, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"RightIdle", L"familiar_brotherbobby.bmp", 2, 2, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"LeftIdle", L"familiar_brotherbobby.bmp", 6, 6, 0.2f, true, false);
	m_RenderBody->CreateAnimation(L"UpIdle", L"familiar_brotherbobby.bmp", 4, 4, 0.2f, true, false);
	m_RenderBody->ChangeAnimation(L"DownIdle");
}

void Familiar_brotherbobby::Update()
{
	Familiar::Update();
}

void Familiar_brotherbobby::FireEvent(const float4& dir)
{

	if (m_CharacterInfo->GetAttackDelayMax() < m_CharacterInfo->GetAttackDelay())
	{
		m_CharacterInfo->SetAttackDelay(0.f);
		Tears* Tear = GetScene()->CreateActor<Tears>();
		float4 _dir = dir;
		
		Tear->PlayFire(this, _dir, float4::ZERO, GetPosition(), m_CharacterInfo->GetAtt(), 200.f, m_CharacterInfo->GetShotRange(), false);

		EngineSound::Play(L"TearFire.mp3", false, 0);
	}
}
