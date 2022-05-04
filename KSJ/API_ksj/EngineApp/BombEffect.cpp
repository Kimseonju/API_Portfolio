#include "BombEffect.h"
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include <EngineRendererBasic.h>
#include "LogicValue.h"
#include <EngineCollision.h>
#include "Player.h"
#include "LogicValue.h"
#include "RoomInfo.h"
#include "PlayScene.h"
#include "Door.h"
#include "PlayScene.h"
//static
//static func


int BombEffect::LayerNumber=0;
BombEffect::BombEffect() : m_RenderEffect(nullptr), m_RenderLayer(nullptr)
, m_Collision(nullptr), m_ColtimeMax(0.3f), m_time(0.f), m_livingtime(0.f)
, m_SecretCheck(false)

{
}

BombEffect::~BombEffect()
{
}

void BombEffect::Start()
{
	SetClassType(L"Bomb");
	m_RenderLayer = CreateRenderer<EngineRendererBasic>(0);
	m_RenderLayer->SetRenderScale({ 192, 128 });
	m_RenderLayer->TransCut_Setting(L"ExplosionLayer.bmp", LayerNumber);
	m_RenderLayer->SetPivotPos({ 0.f,25.f });
	m_RenderLayer->SetAlpha(250);
	NextLayer();

	m_RenderEffect = CreateRenderer<EngineRendererAnim>(1);
	m_RenderEffect->SetRenderScale({ 192, 192 });
	m_RenderEffect->SetPivotPos({ 0.f,-50.f });
	m_RenderEffect->CreateAnimation(L"Play", L"Explosion.bmp", 0, 15, 0.1f, false);
	m_RenderEffect->ChangeAnimation(L"Play");


	m_Collision = CreateCollision<EngineCollision>(static_cast<int>(LogicValue::CollisionGroup::Bomb));
	m_Collision->SetScale({192.f,192.f });

	m_Collision->AddStartEvent(this, &BombEffect::StartCol);
	m_Collision->AddStayEvent(this, &BombEffect::StayCol);
	m_Collision->AddEndEvent(this, &BombEffect::EndCol);
}

void BombEffect::Update()
{
	m_time += EngineTimer::MainTimer.GetFDeltaTime();

	if (nullptr != m_Collision)
	{
		//잠깐 나오는충돌 시간지나면 바로삭제
		if (m_time > m_ColtimeMax)
		{
			if (!m_SecretCheck)
			{
				m_SecretCheck = true;
				OpenSecret();
			}
			
			m_Collision->Off();
		}
	}
	if (m_time > 5.f)
	{
		Death();
	}
}
void BombEffect::OffTask()
{
	Death();
}

void BombEffect::OpenSecret()
{

	Player* player = LogicValue::MainPlayer;
	float4 mapcount = player->GetMapCount();
	RoomInfo* playerRoom = LogicValue::MainScene->GetMap(mapcount);
	RoomInfo* Secretroom = nullptr;
	int dir= 0;
	for (int i = 0; i < 4; ++i)
	{
		//일단 상하좌우 비밀방있는지 탐색
		RoomInfo* room = LogicValue::MainScene->GetMap(mapcount + float4::AllDir[i]);
		if (room == nullptr)
		{
			continue;
		}
		if (room->GetType() == LogicValue::RoomType::Secret)
		{
			Secretroom = room;
			dir = i;
		}
	}
	//만약 비밀방이없다면 종료
	if (nullptr == Secretroom)
	{
		return;
	}

	//위치해있는 문을 가져온다.
	//문과 위치 비교하기
	//0,1,2,3
	//왼,오,위,아
	Door* door= playerRoom->GetDoor(dir);

	if (nullptr == door)
	{
		EngineDebug::AssertMsg("if (nullptr == door)");
	}
	float4 pos = GetPosition();
	float4 DoorPos=door->GetPosition();

	//있을때 처리하기
	//방향까지 알아냄
	//충돌체 사이즈는 192.f,192.f
	//96거리로 상하좌우 탐색하기
	int Left = pos.ix() - 96;
	int Right = pos.ix() + 96;
	int Up = pos.iy() - 96;
	int Down = pos.iy() + 96;

	if (Left > DoorPos.ix() || Right< DoorPos.ix() )
	{
		return;
	}
	if (Up > DoorPos.iy() || Down < DoorPos.iy())
	{
		return;
	}

	if (dir == 0)
		dir = 1;
	else if (dir == 1)
		dir = 0;
	else if (dir == 2)
		dir = 3;
	else if (dir == 3)
		dir = 2;
	//안에있을때 처리하기
	// 클리어상태로 변경하고
	//이미지 출력해야됨
	Secretroom->SetClear(true);
	if (nullptr == Secretroom->GetDoor(dir))
	{
		EngineDebug::AssertMsg("if (nullptr == door)");
	}
	Secretroom->GetDoor(dir)->On();
	Secretroom->GetDoor(dir)->SetSecretOpen();
	//시크릿상태때는 문은 끈상태로 하기
	if (door->IsOn())
	{
		//방은 이미 열려있다.
		return;
	}
	door->On();
	door->SetSecretOpen();

	PlayScene* scene=LogicValue::MainScene;
	scene->MiniMapRender();

	EngineSound::Play(L"secretroomfind.mp3", false, 0);

}

void BombEffect::DebugRender()
{
}

void BombEffect::StartCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void BombEffect::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void BombEffect::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
}
