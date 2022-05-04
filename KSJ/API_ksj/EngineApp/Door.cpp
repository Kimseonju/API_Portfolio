#include "Door.h"

#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
#include "LogicValue.h"
// Static Var
// Static Func


// member Var
Door::Door()
	: m_MainDoor(nullptr), m_Space(nullptr), m_LeftDoor(nullptr), m_RightDoor(nullptr), m_Open(true)
	, m_BossDoorLayer(nullptr), m_Dir(float4::ZERO), m_Timer(0.f)
	, m_Type(LogicValue::RoomType::Max)
	, m_SecretCheck(false)
{
}
Door::~Door()
{

}
// member Func


void Door::SetDoorImage(int _room, const float4& pos)
{
	EngineString str;
	m_Dir = pos;
	if (pos == float4::LEFT)
	{
		str += L"_Left.bmp";
	}
	else if (pos == float4::RIGHT)
	{
		str += L"_Right.bmp";
	}
	else if (pos == float4::DOWN)
	{

		str += L"_Down.bmp";
	}
	else if (pos == float4::UP)
	{
		str += L"_Up.bmp";
	}
	
	if (static_cast<int>(LogicValue::RoomType::Room)==_room
		|| static_cast<int>(LogicValue::RoomType::Shop )== _room)
	{
		{
			EngineString Doorstr = L"NormalDoor";
			Doorstr += str;
			m_MainDoor = CreateRenderer<EngineRendererBasic>(4);
			m_MainDoor->TransCut_Setting(Doorstr, { 0 });

			m_Space = CreateRenderer<EngineRendererBasic>(3);
			m_Space->TransCut_Setting(Doorstr, { 1 });
		}
		{
			EngineString Doorstr = L"LeftDoorAni";
			Doorstr += str;
			m_LeftDoor = CreateRenderer<EngineRendererAnim>(3);
			m_LeftDoor->SetRenderScale({ 128, 128 });
			m_LeftDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_LeftDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
		{
			EngineString Doorstr = L"RightDoorAni";
			Doorstr += str;
			m_RightDoor = CreateRenderer<EngineRendererAnim>(3);
			m_RightDoor->SetRenderScale({ 128, 128 });
			m_RightDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_RightDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
	}
	else if (static_cast<int>(LogicValue::RoomType::Secret) == _room)
	{
		
		{
			EngineString Doorstr = L"SecretDoor";
			Doorstr += str;
			m_MainDoor = CreateRenderer<EngineRendererBasic>(4);
			m_MainDoor->TransCut_Setting(Doorstr, { 0 });

			m_Space = CreateRenderer<EngineRendererBasic>(3);
			m_Space->TransCut_Setting(Doorstr, { 1 });
		}
		{
			EngineString Doorstr = L"LeftAni";
			Doorstr += str;
			m_LeftDoor = CreateRenderer<EngineRendererAnim>(3);
			m_LeftDoor->SetRenderScale({ 128, 128 });
			m_LeftDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_LeftDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
		{
			EngineString Doorstr = L"RightAni";
			Doorstr += str;
			m_RightDoor = CreateRenderer<EngineRendererAnim>(3);
			m_RightDoor->SetRenderScale({ 128, 128 });
			m_RightDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_RightDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
	}
	else if (static_cast<int>(LogicValue::RoomType::Boss)== _room)
	{
		{
			EngineString Doorstr = L"BossDoor";
			Doorstr += str;
			m_MainDoor = CreateRenderer<EngineRendererBasic>(4);
			m_MainDoor->TransCut_Setting(Doorstr, { 0 });

			m_Space = CreateRenderer<EngineRendererBasic>(3);
			m_Space->TransCut_Setting(Doorstr, { 1 });

			float4 PivotPos = pos * 60.f;
			PivotPos.x = -PivotPos.x;
			PivotPos.y = -PivotPos.y;
			m_BossDoorLayer = CreateRenderer<EngineRendererBasic>(2);
			m_BossDoorLayer->TransCut_Setting(Doorstr, { 2 });
			m_BossDoorLayer->SetPivotPos(PivotPos);
			m_BossDoorLayer->SetAlpha(40);
			m_BossDoorLayer->Off();
		}
		{
			EngineString Doorstr = L"LeftDoorAni_Boss";
			Doorstr += str;
			m_LeftDoor = CreateRenderer<EngineRendererAnim>(3);
			m_LeftDoor->SetRenderScale({ 128, 128 });
			m_LeftDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_LeftDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
		{
			EngineString Doorstr = L"RightDoorAni_Boss";
			Doorstr += str;
			m_RightDoor = CreateRenderer<EngineRendererAnim>(3);
			m_RightDoor->SetRenderScale({ 128, 128 });
			m_RightDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_RightDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
		
	}
	else if (static_cast<int>(LogicValue::RoomType::FinalBoss) == _room)
	{
		{
			EngineString Doorstr = L"BossDoor";
			Doorstr += str;
			m_MainDoor = CreateRenderer<EngineRendererBasic>(4);
			m_MainDoor->TransCut_Setting(Doorstr, { 0 });

			m_Space = CreateRenderer<EngineRendererBasic>(3);
			m_Space->TransCut_Setting(Doorstr, { 1 });

			float4 PivotPos = pos * 60.f;
			PivotPos.x = -PivotPos.x;
			PivotPos.y = -PivotPos.y;
		}
		{
			EngineString Doorstr = L"LeftDoorAni_Boss";
			Doorstr += str;
			m_LeftDoor = CreateRenderer<EngineRendererAnim>(3);
			m_LeftDoor->SetRenderScale({ 128, 128 });
			m_LeftDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_LeftDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
		{
			EngineString Doorstr = L"RightDoorAni_Boss";
			Doorstr += str;
			m_RightDoor = CreateRenderer<EngineRendererAnim>(3);
			m_RightDoor->SetRenderScale({ 128, 128 });
			m_RightDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_RightDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}

	}
	else if (static_cast<int>(LogicValue::RoomType::Treasure) == _room)
	{
		{
			EngineString Doorstr = L"TreasureDoor";
			Doorstr += str;
			m_MainDoor = CreateRenderer<EngineRendererBasic>(4);
			m_MainDoor->TransCut_Setting(Doorstr, { 0 });

			m_Space = CreateRenderer<EngineRendererBasic>(3);
			m_Space->TransCut_Setting(Doorstr, { 1 });
		}
		{
			EngineString Doorstr = L"LeftDoorAni";
			Doorstr += str;
			m_LeftDoor = CreateRenderer<EngineRendererAnim>(3);
			m_LeftDoor->SetRenderScale({ 128, 128 });
			m_LeftDoor->CreateAnimation(L"Open", Doorstr , 0, 2, 0.1f, false, true);
			m_LeftDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
		{
			EngineString Doorstr = L"RightDoorAni";
			Doorstr += str;
			m_RightDoor = CreateRenderer<EngineRendererAnim>(3);
			m_RightDoor->SetRenderScale({ 128, 128 });
			m_RightDoor->CreateAnimation(L"Open", Doorstr, 0, 2, 0.1f, false, true);
			m_RightDoor->CreateAnimation(L"Close", Doorstr, 0, 2, 0.1f, false, false);
		}
	}
	m_Type = static_cast<LogicValue::RoomType>(_room);
	if (nullptr == m_MainDoor)
	{
		EngineDebug::AssertMsg("if (nullptr == m_MainDoor)");
	}

	if (nullptr == m_LeftDoor)
	{
		EngineDebug::AssertMsg("if (nullptr == m_LeftDoor)");
	}
	if (nullptr == m_RightDoor)
	{
		EngineDebug::AssertMsg("if (nullptr == m_RightDoor)");
	}
	m_LeftDoor->ChangeAnimation(L"Open");
	m_RightDoor->ChangeAnimation(L"Open");
}
void Door::Start()
{
	SetClassType(L"Door");

	
}
void Door::Update()
{
	if (m_Open)
	{
		if (m_Timer == 0.f)
		{
			float4 pos;
			float4 scale;
			pos = m_Dir;
			pos.x = abs(pos.x);
			pos.y = abs(pos.y);
			pos = pos * 10;
			scale = float4{ m_Dir.x * 40 + 128, m_Dir.y * 40 + 128 };
			m_MainDoor->SetPivotPos({ pos });
			m_MainDoor->SetRenderScale(scale);
			m_Space->SetPivotPos({ pos });
			m_Space->SetRenderScale(scale);
			m_LeftDoor->SetPivotPos({ pos });
			m_LeftDoor->SetRenderScale(scale);
			m_RightDoor->SetPivotPos({ pos });
			m_RightDoor->SetRenderScale(scale);
		}
		if (m_Timer >= 0.1f && m_Timer < 0.2f)
		{
			float4 pos;
			float4 scale;
			pos = m_Dir;
			pos.x = abs(pos.x);
			pos.y = abs(pos.y);
			pos = pos * -10;
			scale = float4{ -m_Dir.x * 40 + 128, -m_Dir.y * 40 + 128 };
			m_MainDoor->SetPivotPos({ pos });
			m_MainDoor->SetRenderScale(scale);
			m_Space->SetPivotPos({ pos });
			m_Space->SetRenderScale(scale);
			m_LeftDoor->SetPivotPos({ pos });
			m_LeftDoor->SetRenderScale(scale);
			m_RightDoor->SetPivotPos({ pos });
			m_RightDoor->SetRenderScale(scale);

		}
		if (m_Timer >= 0.2f)
		{
			float4 pos;
			float4 scale;
			pos = float4::ZERO;
			scale = float4{ 128.f,128.f };
			m_MainDoor->SetPivotPos({ pos });
			m_MainDoor->SetRenderScale(scale);
			m_Space->SetPivotPos({ pos });
			m_Space->SetRenderScale(scale);
			m_LeftDoor->SetPivotPos({ pos });
			m_LeftDoor->SetRenderScale(scale);
			m_RightDoor->SetPivotPos({ pos });
			m_RightDoor->SetRenderScale(scale);
			m_LeftDoor->ChangeAnimation(L"Open");
			m_RightDoor->ChangeAnimation(L"Open");
			if (m_BossDoorLayer != nullptr)
				m_BossDoorLayer->On();
		}

		if (m_Timer < 1.5f)
		{
			m_Timer += EngineTimer::MainTimer.GetFDeltaTime();
		}
	}
	else
	{
		if (m_BossDoorLayer != nullptr)
			m_BossDoorLayer->Off();
		if (m_Timer == 0.f)
		{
			float4 pos;
			float4 scale;
			pos = m_Dir;
			pos.x = abs(pos.x);
			pos.y = abs(pos.y);
			pos = pos *10;
			scale = float4{ m_Dir.x * 40 + 128, m_Dir.y * 40 + 128 };
			m_MainDoor->SetPivotPos({ pos });
			m_MainDoor->SetRenderScale(scale);
			m_Space->SetPivotPos({ pos });
			m_Space->SetRenderScale(scale);
			m_LeftDoor->SetPivotPos({ pos });
			m_LeftDoor->SetRenderScale(scale);
			m_RightDoor->SetPivotPos({ pos });
			m_RightDoor->SetRenderScale(scale);
		}
		if (m_Timer >= 0.1f && m_Timer < 0.2f)
		{
			float4 pos;
			float4 scale;
			pos = m_Dir;
			pos.x = abs(pos.x);
			pos.y = abs(pos.y);
			pos = pos * -10;
			scale = float4{ -m_Dir.x * 40 + 128, -m_Dir.y * 40 + 128 };
			m_MainDoor->SetPivotPos({ pos });
			m_MainDoor->SetRenderScale(scale);
			m_Space->SetPivotPos({ pos });
			m_Space->SetRenderScale(scale);
			m_LeftDoor->SetPivotPos({ pos });
			m_LeftDoor->SetRenderScale(scale);
			m_RightDoor->SetPivotPos({ pos });
			m_RightDoor->SetRenderScale(scale);
		
		}
		if (m_Timer >= 0.2f)
		{
			float4 pos;
			float4 scale;
			pos = float4::ZERO;
			scale = float4{ 128.f,128.f };
			m_MainDoor->SetPivotPos({ pos });
			m_MainDoor->SetRenderScale(scale);
			m_Space->SetPivotPos({ pos });
			m_Space->SetRenderScale(scale);
			m_LeftDoor->SetPivotPos({ pos });
			m_LeftDoor->SetRenderScale(scale);
			m_RightDoor->SetPivotPos({ pos });
			m_RightDoor->SetRenderScale(scale);
		}
		else
		{
			m_LeftDoor->ChangeAnimation(L"Close");
			m_RightDoor->ChangeAnimation(L"Close");
		}
		if (m_Timer < 1.f)
		{
			m_Timer += EngineTimer::MainTimer.GetFDeltaTime();
		}
	}
}

void Door::BossOpen()
{
	if (m_Timer == 0.f)
	{
		float4 pos;
		float4 scale;
		pos = m_Dir;
		pos.x = abs(pos.x);
		pos.y = abs(pos.y);
		pos = pos * 10;
		scale = float4{ m_Dir.x * 40 + 128, m_Dir.y * 40 + 128 };
		m_MainDoor->SetPivotPos({ pos });
		m_MainDoor->SetRenderScale(scale);
		m_Space->SetPivotPos({ pos });
		m_Space->SetRenderScale(scale);
		m_LeftDoor->SetPivotPos({ pos });
		m_LeftDoor->SetRenderScale(scale);
		m_RightDoor->SetPivotPos({ pos });
		m_RightDoor->SetRenderScale(scale);
	}
	if (m_Timer >= 0.1f && m_Timer < 0.2f)
	{
		float4 pos;
		float4 scale;
		pos = m_Dir;
		pos.x = abs(pos.x);
		pos.y = abs(pos.y);
		pos = pos * -10;
		scale = float4{ -m_Dir.x * 40 + 128, -m_Dir.y * 40 + 128 };
		m_MainDoor->SetPivotPos({ pos });
		m_MainDoor->SetRenderScale(scale);
		m_Space->SetPivotPos({ pos });
		m_Space->SetRenderScale(scale);
		m_LeftDoor->SetPivotPos({ pos });
		m_LeftDoor->SetRenderScale(scale);
		m_RightDoor->SetPivotPos({ pos });
		m_RightDoor->SetRenderScale(scale);

	}
	if (m_Timer >= 0.2f)
	{
		float4 pos;
		float4 scale;
		pos = float4::ZERO;
		scale = float4{ 128.f,128.f };
		m_MainDoor->SetPivotPos({ pos });
		m_MainDoor->SetRenderScale(scale);
		m_Space->SetPivotPos({ pos });
		m_Space->SetRenderScale(scale);
		m_LeftDoor->SetPivotPos({ pos });
		m_LeftDoor->SetRenderScale(scale);
		m_RightDoor->SetPivotPos({ pos });
		m_RightDoor->SetRenderScale(scale);
		m_LeftDoor->ChangeAnimation(L"Open");
		m_RightDoor->ChangeAnimation(L"Open");
		if (m_BossDoorLayer != nullptr)
			m_BossDoorLayer->On();
	}

	if (m_Timer < 1.5f)
	{
		m_Timer += EngineTimer::MainTimer.GetFDeltaTime();
	}
}

void Door::BossClose()
{
}
