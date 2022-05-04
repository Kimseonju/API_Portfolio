#include "Player.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "Player_ItemCostume.h"
#include "Tears.h"
#include <EngineCollision.h>
#include "Bomb.h"
#include "ProtectionFly.h"
#include "PlayScene.h"
#include "RoomInfo.h"
#include "Familiar.h"
#include "ActiveItem.h"
#include "ItemEffect.h"
// Static Var
// Static Func


// member Var
Player::Player() : Speed(1.f), m_RenderHead(nullptr), m_RenderBody(nullptr), m_MapCount(float4::ZERO), m_OldMapCount(float4::ZERO)
, m_CamTime(0.f), m_CamMove(false), m_CamStartPos(float4::ZERO), m_CamEndPos(float4::ZERO), m_MapMove(true)
, m_State(ePlayerState::IDLE), m_GracePeriod(0.f), m_GracePeriodMax(1.f), m_Invincible(false)
, m_BodyCol(nullptr), m_RenderEmotion(nullptr), m_WallUpDownCollision(Dir::MAX), m_WallLeftRightCollision(Dir::MAX), m_HeadDir(Dir::DOWN), m_BodyDir(Dir::DOWN)
, m_PrevBodyDir(Dir::DOWN), m_PrevHeadDir(Dir::DOWN), m_PrevState(ePlayerState::IDLE), m_Input(true)
, m_DamageOnOffCount(0.f), m_DamageOnOffCountMax(0.1f), m_Itemfunction(nullptr), m_bCollectionItem(false)
, m_bCheckBomb(false), m_HeadCol(nullptr), m_view(false)
, m_DamageAni(nullptr), m_Fly(false), m_MapClear(false)
, m_ActiveItem(nullptr)
, m_CharacterInfo(nullptr)
, m_MultiShot(1)
, m_MultiShotRange(50.f)
, m_bGuided(false)
, m_DebugInvincible(false)

{
}

Player::~Player()
{
	if (m_CharacterInfo)
		delete m_CharacterInfo;
	m_CharacterInfo = nullptr;
}
// member Func

void Player::Start()
{
	m_MapCount.x = 2;
	m_MapCount.y = 2;
	SetSize({ 40.f,40.f });
	SetClassType(L"Player");
	m_OldMapCount = m_MapCount;
	m_CharacterInfo = new CCharacterInfo();
	m_CharacterInfo->SetSpeed(100.f);
	m_CharacterInfo->SetHP(m_CharacterInfo->GetHPMax());
	m_CharacterInfo->SetMaxSpeed(300.f);
	m_CharacterInfo->SetShotSpeed(300.f);
	m_CharacterInfo->SetCoin(90);
	m_CharacterInfo->SetBomb(90);
	m_CharacterInfo->SetKey(50);
	//이미지
	{

		{
			EngineRendererBasic* NewShadow = CreateRenderer<EngineRendererBasic>(1);
			NewShadow->TransCut_Setting(L"shadow.bmp", 0);
			NewShadow->SetRenderScale({ 36, 16 });
			NewShadow->SetPivotPos({ 0, 35 });
			NewShadow->SetAlpha(100);
		}


		m_RenderBody = CreateRenderer<EngineRendererAnim>(500);
		m_RenderBody->SetRenderScale({ 64, 64 });
		m_RenderBody->CreateAnimation(L"DownMove", L"Player_down.bmp", 0, 9);
		m_RenderBody->CreateAnimation(L"RightMove", L"Player_right.bmp", 0, 9);
		m_RenderBody->CreateAnimation(L"LeftMove", L"Player_left.bmp", 0, 9);
		m_RenderBody->CreateAnimation(L"UpMove", L"Player_up.bmp", 0, 9);

		m_RenderBody->CreateAnimation(L"DownIdle", L"Player_down.bmp", 0, 0);
		m_RenderBody->CreateAnimation(L"RightIdle", L"Player_right.bmp", 0, 0);
		m_RenderBody->CreateAnimation(L"LeftIdle", L"Player_left.bmp", 0, 0);
		m_RenderBody->CreateAnimation(L"UpIdle", L"Player_up.bmp", 6, 6, 0.5f, false);
		m_RenderBody->SetPivotPos({ 0,  25 });


		m_BodyFSM.CreateState(L"IDLE", this, &Player::BodyIDLEStay, &Player::BodyIDLEStart);
		m_BodyFSM.CreateState(L"MOVE", this, &Player::BodyMOVEStay, &Player::BodyMOVEStart);
		m_BodyFSM.ChangeState(L"IDLE");


		m_RenderHead = CreateRenderer<EngineRendererAnim>(500);
		m_RenderHead->SetRenderScale({ 64, 64 });
		m_RenderHead->CreateAnimation(L"DownIdle", L"Player_head.bmp", 1, 1);
		m_RenderHead->CreateAnimation(L"RightIdle", L"Player_head.bmp", 3, 3);
		m_RenderHead->CreateAnimation(L"UpIdle", L"Player_head.bmp", 5, 5);
		m_RenderHead->CreateAnimation(L"LeftIdle", L"Player_head.bmp", 7, 7);

		m_RenderHead->CreateAnimation(L"DownFire", L"Player_head.bmp", 0, 1, 0.2f);
		m_RenderHead->CreateAnimation(L"RightFire", L"Player_head.bmp", 2, 3, 0.2f);
		m_RenderHead->CreateAnimation(L"UpFire", L"Player_head.bmp", 4, 5, 0.2f);
		m_RenderHead->CreateAnimation(L"LeftFire", L"Player_head.bmp", 6, 7, 0.2f);

		m_HeadFSM.CreateState(L"IDLE", this, &Player::HeadIDLEStay, &Player::HeadIDLEStart);
		m_HeadFSM.CreateState(L"FIRE", this, &Player::HeadFIREStay, &Player::HeadFIREStart);
		m_HeadFSM.ChangeState(L"IDLE");


		m_RenderEmotion = CreateRenderer<EngineRendererAnim>(500);
		m_RenderEmotion->SetRenderScale({ 128, 128 });
		m_RenderEmotion->CreateAnimation(L"Damage", L"PlayerEmotion.bmp", 6, 6, 0.6f, false);
		m_RenderEmotion->CreateAnimation(L"Item", L"PlayerEmotion.bmp", 5, 5, 1.f, false);
		m_RenderEmotion->CreateAnimation(L"Die", L"PlayerEmotion.bmp", 0, 1, 0.5f, false);
		m_RenderEmotion->CreateAnimation(L"Idle", L"PlayerEmotion.bmp", 11, 11, 0.5f, false);
		m_RenderEmotion->SetPivotPos({ 0,  10 });
		m_EmotionFSM.CreateState(L"IDLE", this, &Player::EmotionIDLEStay, &Player::EmotionIDLEStart);
		m_EmotionFSM.CreateState(L"DAMAGE", this, &Player::EmotionDAMAGEStay, &Player::EmotionDAMAGEStart);
		m_EmotionFSM.CreateState(L"ITEM", this, &Player::EmotionItemStay, &Player::EmotionItemStart);
		m_EmotionFSM.CreateState(L"DIE", this, &Player::EmotionDieStay, &Player::EmotionDieStart);
		m_EmotionFSM.ChangeState(L"IDLE");

		m_RenderEmotion->ChangeAnimation(L"Idle");
		m_RenderEmotion->Off();

		//ItemEffect = CreateRenderer<EngineRendererAnim>(10002);

		m_RenderBody->ChangeAnimation(L"DownIdle");
		m_RenderHead->ChangeAnimation(L"DownIdle");
	}
	//충돌
	{

		m_BodyCol = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Player));
		m_BodyCol->SetPivotPos({ 0.f, 30.f });
		m_BodyCol->SetScale({ 30.f,20.f });
		m_BodyCol->AddStartEvent(this, &Player::BodyStartCol);
		m_BodyCol->AddStayEvent(this, &Player::BodyStayCol);
		m_BodyCol->AddEndEvent(this, &Player::BodyEndCol);

		m_HeadCol = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::PlayerHead));
		m_HeadCol->SetPivotPos({ 0.f, 0.f });
		m_HeadCol->SetScale({ 40.f,30.f });
		m_HeadCol->AddStartEvent(this, &Player::HeadStartCol);
		m_HeadCol->AddStayEvent(this, &Player::HeadEndCol);
		m_HeadCol->AddEndEvent(this, &Player::HeadStayCol);
	}
	float4 Size = EngineWindow::GetSize();
	SetPosition({ Size.x * m_MapCount.x + Size.hx(), Size.y * m_MapCount.x + Size.hy() });
	GetScene()->SetCamPos({ Size.x * m_MapCount.x, Size.y * m_MapCount.x });


}


void Player::KeyCheck()
{
	MovePos = float4::ZERO;

	m_HeadDir = Dir::DOWN;
	m_BodyDir = Dir::DOWN;
	if (!m_Input)
		return;


	if (true == EngineInput::IsDown(L"Bomb"))
	{
		if (m_CharacterInfo->GetBomb() > 0)
		{
			m_CharacterInfo->BombSub();
			Bomb* pBomb = GetScene()->CreateActor<Bomb>();
			float4 pos = GetPosition();
			pos.y += 30.f;
			pBomb->SetPosition(pos);
			m_bCheckBomb = true;
			RoomInfo* room = LogicValue::MainScene->GetMap(m_MapCount.ix(), m_MapCount.iy());

			pBomb->SetRoom(room);
			room->PushActor(pBomb);
		}
	}

	if (true == EngineInput::IsDown(L"ActiveItem"))
	{
		//액티브아이템이있으면?
		if (m_ActiveItem)
		{
			//수행
			m_ActiveItem->Play();
		}
	}

	if (true == EngineInput::IsPress(L"L"))
	{
		MovePos = MovePos + float4::LEFT;
		m_BodyDir = Dir::LEFT;
		m_HeadDir = Dir::LEFT;
	}
	if (true == EngineInput::IsPress(L"R"))
	{
		MovePos = MovePos + float4::RIGHT;
		m_BodyDir = Dir::RIGHT;
		m_HeadDir = Dir::RIGHT;
	}
	if (true == EngineInput::IsPress(L"U"))
	{
		MovePos = MovePos + float4::UP;
		m_BodyDir = Dir::UP;
		m_HeadDir = Dir::UP;
	}
	if (true == EngineInput::IsPress(L"D"))
	{
		MovePos = MovePos + float4::DOWN;
		m_BodyDir = Dir::DOWN;
		m_HeadDir = Dir::DOWN;
	}

	if (m_BodyDir == Dir::MAX)
	{
		m_BodyDir = m_PrevBodyDir;
		m_HeadDir = m_PrevBodyDir;
	}
	else {
		m_PrevBodyDir = m_BodyDir;
	}

	if (true == EngineInput::IsPress(L"LFire"))
	{
		m_HeadDir = Dir::LEFT;
	}
	if (true == EngineInput::IsPress(L"RFire"))
	{
		m_HeadDir = Dir::RIGHT;
	}
	if (true == EngineInput::IsPress(L"UFire"))
	{
		m_HeadDir = Dir::UP;
	}
	if (true == EngineInput::IsPress(L"DFire"))
	{
		m_HeadDir = Dir::DOWN;
	}

	if (m_HeadDir == Dir::MAX)
	{
		m_HeadDir = m_PrevHeadDir;
	}
	else {
		m_PrevHeadDir = m_HeadDir;
	}
	m_CharacterInfo->SetDir(MovePos);
}

void Player::Update()
{
	//키입력
	if (m_CharacterInfo->GetHP() <= 0)
	{
		m_State = ePlayerState::DIE;
	}
	KeyCheck();
	m_CharacterInfo->SetAttackDelay(m_CharacterInfo->GetAttackDelay() + EngineTimer::FDeltaTime());

	m_BodyFSM.Update();
	m_HeadFSM.Update();
	m_EmotionFSM.Update();
	//맵충돌
	//카메라이동
	MapMove();
	//만약 map이 클리어됬다면 (LateUpdate돌리고 돌아옴)
	if (m_MapClear)
	{
		m_MapClear = false;
		int size = static_cast<int>(m_Familiar.size());
		for (int i = 0; i < size; ++i)
		{	//패밀리어들이 이벤트실행
			m_Familiar[i]->FamiliarEvent();
		}

	}

	if (m_Fly)
	{
		m_RenderBody->Off();
		m_RenderHead->SetPivotPos({ 0,  -10 });
		m_RenderBody->SetPivotPos({ 0,  -10 });
		m_RenderEmotion->SetPivotPos({ 0,  0 });
		m_HeadCol->SetPivotPos({ 0.f, -10.f });


		std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
		std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
		for (; start != end; ++start)
		{
			(*start)->GetRenderHead()->SetPivotPos({ 0,-10 });
		}
		SetRenderOrderFly();

	}

	//Z키 디버그(이미지출력)
	if (true == EngineInput::IsDown(L"Debug"))
	{
		GetScene()->DebugOnOff();
	}

	if (true == EngineInput::IsDown(L"Debug2"))
	{
		m_DebugInvincible = !m_DebugInvincible;
	}
}

void Player::UpdatePrev()
{
	m_CharacterInfo->SetDir(float4::ZERO);
}

void Player::UpdateNext()
{
	m_CharacterInfo->Update();
	MapCollision();
	MovePosition(m_CharacterInfo->GetUpdateSpeed());
}




void Player::CamMoveCheck(const float4& _dir)
{
	if (m_CamMove)
	{
		return;
	}
	m_CamStartPos = GetScene()->GetCamPos();
	m_CamEndPos = GetScene()->GetCamPos();
	float4 MapSize = EngineWindow::GetSize();
	m_OldMapCount = m_MapCount;
	if (float4::LEFT == _dir)
	{
		m_CamTime = 0.0f;
		m_CamEndPos += float4::LEFT * MapSize.x;
		m_CamMove = true;
		MovePosition({ -MapSize.ix() + 734,0 });
		--m_MapCount.x;
	}
	if (float4::RIGHT == _dir)
	{
		m_CamTime = 0.0f;
		m_CamEndPos += float4::RIGHT * MapSize.x;
		m_CamMove = true;
		MovePosition({ +MapSize.ix() - 734,0 });
		++m_MapCount.x;
	}
	if (float4::UP == _dir)
	{
		m_CamTime = 0.0f;
		m_CamEndPos += float4::UP * MapSize.y;
		m_CamMove = true;
		MovePosition({ 0,306 - MapSize.iy() });
		--m_MapCount.y;
	}
	if (float4::DOWN == _dir)
	{
		m_CamTime = 0.0f;
		m_CamEndPos += float4::DOWN * MapSize.y;
		m_CamMove = true;
		MovePosition({ 0,-306 + MapSize.iy() });
		++m_MapCount.y;
	}

	//방이동했으니 패밀리어들도 방이동해야한다.
	//아이작 몸에 달려있는 아이템은 부모가 아이작으로되어있지만
	//패밀리어들은 부모가없음
	int size = static_cast<int>(m_Familiar.size());
	for (int i = 0; i < size; ++i)
	{
		m_Familiar[i]->SetPosition(GetPosition());
	}

}
void Player::MapMove()
{

	if (true == m_CamMove)
	{
		m_Input = false;
		m_CharacterInfo->StopSpeed();
		m_CamTime += EngineTimer::FDeltaTime(6);
		float4 CurPos = float4::Lerp2DMax(m_CamStartPos, m_CamEndPos, m_CamTime);
		GetScene()->SetCamPos(CurPos);
		if (1.0F <= m_CamTime)
		{
			m_Input = true;
			m_CamMove = false;
			m_MapMove = true;
		}
	}
}
void Player::DebugRender()
{

	int posy = 10;
	EngineString PrintText = L"RenderBody";
	PrintText = L"Position";
	PrintText += L" X ";
	PrintText += GetPosition().ix();
	PrintText += L" Y ";
	PrintText += GetPosition().iy();

	posy += 20;
	DebugTextout(PrintText, 10, posy);

	PrintText = L"Map";
	PrintText += L" X ";
	PrintText += m_MapCount.ix();
	PrintText += L" Y ";
	PrintText += m_MapCount.iy();
	posy += 20;
	DebugTextout(PrintText, 10, posy);
	PrintText = L"속도  ";

	PrintText += static_cast<int>(m_CharacterInfo->GetAccelSpeed().Len());
	posy += 20;
	DebugTextout(PrintText, 10, posy);

	{
		PrintText = L"상태: ";
		if (m_State == ePlayerState::IDLE)
		{
			PrintText += L"Idle";
		}
		else if (m_State == ePlayerState::MOVE)
		{
			PrintText += L"Move";
		}
		else if (m_State == ePlayerState::ATTACK)
		{
			PrintText += L"Attack";
		}
		else if (m_State == ePlayerState::DAMAGE)
		{
			PrintText += L"Damage";
		}
		else if (m_State == ePlayerState::DIE)
		{
			PrintText += L"Die";
		}
		posy += 20;
		DebugTextout(PrintText, 10, posy);
	}

	PrintText = L"무적: ";
	if (m_DebugInvincible)
	{
		PrintText += L"True";
	}
	else
	{
		if (m_Invincible)
		{
			PrintText += L"True";
		}
		else
		{
			PrintText += L"False";
		}

	}
	
	
	posy += 20;
	DebugTextout(PrintText, 10, posy);

	posy += 20;
	PrintText = L"";
	PrintText += EngineString::ToString(static_cast<int>((1.f / EngineTimer::MainTimer.GetFDeltaTime())));
	DebugTextout(PrintText, 10, posy);
}

void Player::SetHeadAnimFrameTimer(float _Time)
{
	m_RenderHead->SetAllAnimTimer(_Time);
	//캐릭터에게 달려있는 아이템들 조작
	std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	for (; start != end; ++start)
	{
		(*start)->SetAnimFrameTimer(_Time);
	}
}

//Move, Idle, Fire
void Player::ChangeHeadAnimation(const EngineString& _Str)
{
	//Move, Idle, Fire
	EngineString NewString;

	switch (m_HeadDir)
	{
	case Dir::LEFT:
		NewString += L"Left";
		break;

	case Dir::RIGHT:
		NewString += L"Right";
		break;
	case Dir::UP:
		NewString += L"Up";
		break;
	case Dir::DOWN:
		NewString += L"Down";
		break;
	case Dir::MAX:
		NewString += L"Down";
		break;
	}
	NewString += _Str;
	m_RenderHead->ChangeAnimation(NewString);
	//캐릭터에게 달려있는 아이템들 조작
	std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	for (; start != end; ++start)
	{
		(*start)->ChangeAnimationdir(NewString);
	}
}

void Player::ChangeFamiliarAnimation(const EngineString& _Str)
{
	//Move, Idle, Fire
	EngineString NewString;

	switch (m_HeadDir)
	{
	case Dir::LEFT:
		NewString += L"Left";
		break;

	case Dir::RIGHT:
		NewString += L"Right";
		break;
	case Dir::UP:
		NewString += L"Up";
		break;
	case Dir::DOWN:
		NewString += L"Down";
		break;
	case Dir::MAX:
		NewString += L"Down";
		break;
	}
	NewString += _Str;
	int size = static_cast<int>(m_Familiar.size());
	for (int i = 0; i < size; ++i)
	{
		m_Familiar[i]->ChangeAnimationdir(NewString);
	}
}
//Move, Idle, Fire
void Player::ChangeBodyAnimation(const EngineString& _Str)
{

	EngineString NewString;
	switch (m_BodyDir)
	{
	case Dir::LEFT:
		NewString += L"Left";
		break;

	case Dir::RIGHT:
		NewString += L"Right";
		break;
	case Dir::UP:
		NewString += L"Up";
		break;
	case Dir::DOWN:
		NewString += L"Down";
		break;
	case Dir::MAX:
		NewString += L"Down";
		break;
	}
	NewString += _Str;
	m_RenderBody->ChangeAnimation(NewString);
}

void Player::ChangeEmotionAnimation(const EngineString& _Str)
{
}


void Player::ProtectionActorSort()
{
	int size = static_cast<int>(m_ProtectionFly.size());
	float Angle = static_cast<float>(360) / size;
	for (int i = 0; i < m_ProtectionFly.size(); ++i)
	{
		m_ProtectionFly[i]->SetAngle(static_cast<float>(Angle) * i);
	}
}

void Player::FamiliarPush_TargetSetting(Familiar* _Actor)
{
	int size = static_cast<int>(m_Familiar.size());
	if (size == 0)
	{
		//없으면 플레이어를 기반
		_Actor->SetTarget(this);
	}
	else
	{
		//아니라면 맨 끝 패밀리어를 타겟으로 잡는다.
		_Actor->SetTarget(m_Familiar[size - 1]);
	}
	//이후푸쉬
	m_Familiar.push_back(_Actor);
}

void Player::Die_recovery()
{
	InputOn();
	m_CharacterInfo->SetHP(m_CharacterInfo->GetHPMax());
	//m_CharacterInfo->SetHP(2);

	m_RenderEmotion->ChangeAnimation(L"Idle");
	m_RenderEmotion->Off();
	m_RenderHead->On();
	m_RenderBody->On();
	m_Invincible = false;
	std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	for (; start != end; ++start)
	{
		(*start)->On();
	}
	m_BodyCol->On();
	m_HeadCol->On();
	m_State = ePlayerState::IDLE;

	m_EmotionFSM.ChangeState(L"IDLE");
}

void Player::SetRenderOrderFly()
{
	m_RenderEmotion->SetOrder(15000);
	m_RenderHead->SetOrder(15000); 
	m_RenderBody->SetOrder(15000);
	std::list<Player_ItemCostume*>::iterator start = ItemCostume.begin();
	std::list<Player_ItemCostume*>::iterator end = ItemCostume.end();
	for (; start != end; ++start)
	{
		(*start)->SetCharacterFly();
	}
}
