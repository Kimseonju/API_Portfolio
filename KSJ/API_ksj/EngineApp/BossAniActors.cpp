#include "BossAniActors.h"
#include <EngineRendererBasic.h>
#include "LogicValue.h"
//static
//static func


BossAniActors::BossAniActors() :
	PlayerTitle(nullptr), PlayerBackground(nullptr), PlayerBody(nullptr), VS(nullptr),
	BossTitle(nullptr), BossBackground(nullptr), BossBody(nullptr), Background(nullptr)
	, m_MoveCount(-1), m_bMove(false), m_MoveSpeed(0.f), VSAlpha(0), m_Time(0.f)
	, m_PlayerTitleStartPos(float4::ZERO)
	, m_BossTitleStartPos(float4::ZERO)
	, m_StartPos(float4::ZERO)
	, m_EndPos(float4::ZERO)

{
}

BossAniActors::~BossAniActors()
{
}

void BossAniActors::Start()
{
	BossName = L"FlyBoss";
	Background = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI1));
	Background->TransSetting(L"BossAniBackground.bmp", { 960, 540 });
	Background->CamPosOff();
	Background->TransNotCenter();
	//PivotPos좌표는 입력완료
	//가져오면서 x값에따라 움직이기
	m_LeftActor.reserve(5);
	m_RightActor.reserve(5);
	m_LeftStartpos.reserve(5);
	m_RightStartpos.reserve(5);

	PlayerTitle = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI2));
	PlayerTitle->TransSetting(L"TitlePlayer.bmp", { 300, 150 });
	PlayerTitle->CamPosOff();
	PlayerTitle->SetPivotPos({ 198.f,97.f });

	PlayerBackground = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI1));
	PlayerBackground->TransSetting(L"PlayerBackground_BossAni.bmp", { 344, 92 });
	PlayerBackground->CamPosOff();
	PlayerBackground->SetPivotPos({ 200.f,425.f });
	m_LeftActor.push_back(PlayerBackground);

	PlayerBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI1));
	PlayerBody->TransSetting(L"PlayerBossAni.bmp", { 224, 156 });
	PlayerBody->CamPosOff();
	PlayerBody->SetPivotPos({ 200.f,380.f });
	m_LeftActor.push_back(PlayerBody);

	VS = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI2));
	VS->TransSetting(L"vs.bmp", { 300, 150 });
	VS->CamPosOff();
	VS->SetPivotPos({ 445, 90 });
	//알파
	VSAlpha = 2.55f;
	int iAlpha = static_cast<int>((VSAlpha * 100.0f));
	VS->SetAlpha(iAlpha);

	BossTitle = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI2));
	BossTitle->TransSetting(L"DukeOfFliesTitle.bmp", { 300, 150 });
	BossTitle->CamPosOff();
	BossTitle->SetPivotPos({ 740, 90 });

	BossBackground = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI1));
	BossBackground->TransSetting(L"BossBackground_BossAni.bmp", { 520, 140 });
	BossBackground->CamPosOff();
	BossBackground->SetPivotPos({ 710, 435 });
	m_RightActor.push_back(BossBackground);

	BossBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::BossAniUI1));
	BossBody->TransSetting(L"DukeOfFliesBossAni.bmp", { 384, 384 });
	BossBody->CamPosOff();
	BossBody->SetPivotPos({ 710, 300 });
	m_RightActor.push_back(BossBody);

	for (int i = 0; i < m_LeftActor.size(); ++i)
	{
		float4 pos = m_LeftActor[i]->GetPivotPos();
		pos.x -= 400;
		m_LeftActor[i]->SetPivotPos(pos);
	}

	for (int i = 0; i < m_RightActor.size(); ++i)
	{
		float4 pos = m_RightActor[i]->GetPivotPos();
		pos.x += 400;
		m_RightActor[i]->SetPivotPos(pos);
	}

	float4 pos = PlayerTitle->GetPivotPos();
	pos.x -= 400;
	PlayerTitle->SetPivotPos(pos);

	pos = BossTitle->GetPivotPos();
	pos.x += 400;
	BossTitle->SetPivotPos(pos);

}

void BossAniActors::Update()
{
	if (m_MoveCount >= 2)
	{
		VSFadeOut();
	}
	if (m_bMove)
	{
		m_Time += EngineTimer::FDeltaTime(m_MoveSpeed);

		if (0 == m_MoveCount || 2 == m_MoveCount)
		{
			float4 startpos = m_PlayerTitleStartPos;
			float4 CurPos = float4::Lerp2DMax(startpos, startpos + m_EndPos, m_Time);
			PlayerTitle->SetPivotPos(CurPos);

			startpos = m_BossTitleStartPos;
			CurPos = float4::Lerp2DMax(startpos, startpos - m_EndPos, m_Time);
			BossTitle->SetPivotPos(CurPos);
		}

		for (int i = 0; i < m_LeftActor.size(); ++i)
		{
			float4 startpos = m_LeftStartpos[i];
			float4 CurPos = float4::Lerp2DMax(startpos, startpos + m_EndPos, m_Time);
			m_LeftActor[i]->SetPivotPos(CurPos);
		}

		for (int i = 0; i < m_RightActor.size(); ++i)
		{
			float4 startpos = m_RightStartpos[i];
			float4 CurPos = float4::Lerp2DMax(startpos, startpos - m_EndPos, m_Time);
			m_RightActor[i]->SetPivotPos(CurPos);
		}
		if (1.0F <= m_Time)
		{
			m_bMove = false;
		}
	}
	else
	{
		++m_MoveCount;
		if (0 == m_MoveCount)
		{
			m_EndPos.x = 370;
			m_MoveSpeed = 5.f;
			m_bMove = true;
			m_Time = 0.f;
		}
		else if (1 == m_MoveCount)
		{

			m_EndPos.x = 50;
			m_MoveSpeed = 0.5f;
			m_bMove = true;
			m_Time = 0.f;
		}

		else if (2 == m_MoveCount)
		{

			m_EndPos.x = -600;
			m_MoveSpeed = 5.f;
			m_bMove = true;
			m_Time = 0.f;
		}
		m_LeftStartpos.clear();
		m_RightStartpos.clear();
		m_PlayerTitleStartPos = PlayerTitle->GetPivotPos();
		m_BossTitleStartPos = BossTitle->GetPivotPos();
		for (int i = 0; i < m_LeftActor.size(); ++i)
		{
			m_LeftStartpos.push_back(m_LeftActor[i]->GetPivotPos());
		}
		for (int i = 0; i < m_RightActor.size(); ++i)
		{
			m_RightStartpos.push_back(m_RightActor[i]->GetPivotPos());
		}
	}
}

void BossAniActors::BossSet(const EngineString& _Boss)
{
	BossName = _Boss;
	//여러개보스용 미리선언해놓기
	EngineString _str = _Boss + L"Title";
	_str += L".bmp";
	BossTitle->TransCut_Setting(_str, 0);

	_str = _Boss + L"BossAni";
	_str += L".bmp";
	BossBody->TransCut_Setting(_str, 0);
}

void BossAniActors::VSFadeOut()
{

	VSAlpha -= EngineTimer::MainTimer.GetFDeltaTime() * 5;
	int iAlpha = 0;
	if (0.0f >= VSAlpha)
	{
		VSAlpha = 0.0f;
		iAlpha = 0;

	}
	else {
		iAlpha = static_cast<int>((VSAlpha * 100.0f));
	}
	VS->SetAlpha(iAlpha);

}

void BossAniActors::DeathTask()
{
	if (BossName == L"FlyBoss")
	{
		EngineSound::Play(L"BossBGM.mp3", true, 10);
		EngineSound::Volume(L"BossBGM.mp3", 0.7f);
	}
	else if (BossName == L"Mom")
	{
		EngineSound::Play(L"MomFightBGM.mp3", true, 10);
		EngineSound::Volume(L"MomFightBGM.mp3", 0.7f);
	}

}
