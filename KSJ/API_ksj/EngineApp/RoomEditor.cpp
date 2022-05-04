#include "RoomEditor.h"
#include <EngineWindow.h>

#include "LogicValue.h"

//아이템
#include "Itemaltar.h"
#include "Item.h"

//맵오브젝트헤더
#include "Poop.h"
#include "Stone.h"
#include "Bomb.h"
#include "BonFire.h"

//적헤더
#include "Fly.h"
#include "Pooter.h"
#include "Boomfly.h"
#include "full_fly.h"
#include "Deathshead.h"
#include "Nerveending.h"
#include "Psychicmaw.h"
#include "Psychic_horf.h"
#include "Onetooth.h"
#include "Redboomfly.h"
#include "Horf.h"
#include "Dinga.h"
#include "Dip.h"
#include "Host.h"
#include "Moms_hand.h"
#include "Redmaw.h"
#include "Squirt.h"
#include "Sucker.h"
#include "Turret.h"


//Grid

#include "Spikes.h"
#include "PitLeftTop.h"
#include "PitTop.h"
#include "PitRightTop.h"
#include "PitLeft.h"
#include "PitCenter.h"
#include "PitRight.h"
#include "PitLeftBottom.h"
#include "PitBottom.h"
#include "PitRightBottom.h"

#include "RoomEditorBackground.h"
#include <EngineInput.h>
#include "Enemy.h"
#include <EngineFile.h>
#include <typeinfo>
#include "BoxItem.h"
//static
//static func


RoomEditor::RoomEditor() :SelectActor(LogicValue::EditorActorType::Fly)
, SelectRoom(LogicValue::RoomInfoGroup::Room1)


{
}

RoomEditor::~RoomEditor()
{
}

void RoomEditor::Start()
{
	//여러개 방타입 만들어야댄당..
	RoomEditorBackground* pRenderer = CreateActor<RoomEditorBackground>();

	EngineActor* pActor = CreateActor<Fly>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Pooter>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Boomfly>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<full_fly>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);


	pActor = CreateActor<Deathshead>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Nerveending>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);


	pActor = CreateActor<Psychicmaw>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);
	pActor = CreateActor<Psychic_horf>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Onetooth>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);
	pActor = CreateActor<Redboomfly>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Bomb>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<BonFire>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Poop>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Stone>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Horf>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Dinga>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Dip>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Host>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);
	pActor = CreateActor<Moms_hand>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Redmaw>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);


	pActor = CreateActor<Squirt>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Sucker>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<Turret>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);





	pActor = CreateActor<Spikes>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitLeftTop>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitTop>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitRightTop>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitLeft>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitCenter>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitRight>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitLeftBottom>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitBottom>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	pActor = CreateActor<PitRightBottom>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);


	pActor = CreateActor<BoxItem>();
	pActor->SetPosition({ 800.f,80.f });
	pActor->Off();
	m_UIActor.push_back(pActor);

	m_UIActor[0]->On();

	//모든방을 만든다.
	for(int i=0; i< static_cast<int>(LogicValue::RoomInfoGroup::Max); ++i)
	{
		if (m_AllActor.end() == m_AllActor.find((LogicValue::RoomInfoGroup)i))
		{
			m_AllActor.insert(std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::value_type((LogicValue::RoomInfoGroup)i, std::list<EngineActor*>()));
		}
	}

}

void RoomEditor::SceneUpdate()
{
	for (int i = 0; i < m_UIActor.size(); ++i)
	{
		if (i == static_cast<int>(SelectActor))
		{
			m_UIActor[i]->On();
		}
		else
			m_UIActor[i]->Off();
	}

	//방마다 그림그리게 선택된 방만 On 그외 Off 설정
	std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::iterator Start = m_AllActor.begin();
	std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::iterator End = m_AllActor.end();

	for (; Start != End; ++Start)
	{

		std::list<EngineActor*>& _RoomAllActor = Start->second;

		std::list<EngineActor*>::iterator ActorStart = _RoomAllActor.begin();
		std::list<EngineActor*>::iterator ActorEnd = _RoomAllActor.end();

		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			if (Start->first == SelectRoom)
			{ //선택된방 키자
				(*ActorStart)->On();
			}
			else
			{ //선택되지 않은방 끄자
				(*ActorStart)->Off();
			}
		}

	}

	if (EngineInput::IsUp(L"Save"))
	{
		Save();
	}
	else if (EngineInput::IsUp(L"Load"))
	{
		Load();
	}
	if (EngineInput::IsUp(L"RoomPrev"))
	{
		int num = static_cast<int>(SelectRoom) - 1;
		if (num < 0)
		{
			num = static_cast<int>(LogicValue::RoomInfoGroup::Max) - 1;
		}
		SelectRoom = (LogicValue::RoomInfoGroup)num;
		//방이 안만들어져있으면 오류
		if (m_AllActor.end() == m_AllActor.find(SelectRoom))
		{
			EngineDebug::AssertMsg("if (m_AllActor.end() == m_AllActor.find(SelectRoom))");
		}
	}
	if (EngineInput::IsUp(L"RoomNext"))
	{
		int num = static_cast<int>(SelectRoom) + 1;
		if (num == static_cast<int>(LogicValue::RoomInfoGroup::Max))
		{
			num = 0;
		}
		SelectRoom = (LogicValue::RoomInfoGroup)num;
		//방이 안만들어져있으면 오류
		if (m_AllActor.end() == m_AllActor.find(SelectRoom))
		{
			EngineDebug::AssertMsg("if (m_AllActor.end() == m_AllActor.find(SelectRoom))");
		}
	}


	if (EngineInput::IsPress(L"Create"))
	{
		//만약 없으면 오류
		if (m_AllActor.end() == m_AllActor.find(SelectRoom))
		{
			EngineDebug::AssertMsg("if (m_AllActor.end() == m_AllActor.find(SelectRoom))");
		}
		float4 MousePos = EngineWindow::MousePos();

		std::list<EngineActor*>::iterator	iter = m_AllActor[SelectRoom].begin();
		std::list<EngineActor*>::iterator	iterEnd = m_AllActor[SelectRoom].end();

		bool inCheck = false;
		for (; iter != iterEnd; ++iter)
		{
			float4 Pos = (*iter)->GetPosition();
			float4 Size = (*iter)->GetSize();

			if (MousePos.ix() < Pos.ix() - Size.ix() || MousePos.ix() > Pos.ix() + Size.ix())
			{
				//가로 안에없다
				continue;
			}

			if (MousePos.iy() <= Pos.iy() - Size.iy() || MousePos.iy() >= Pos.iy() + Size.iy())
			{
				//세로안에없다
				continue;
			}
			inCheck = true;
		}
		if (!inCheck)
		{

			EngineActor* pActor=nullptr;
			switch (SelectActor)
			{
			case LogicValue::EditorActorType::Fly:
				pActor = CreateActor<Fly>();
				break;
			case LogicValue::EditorActorType::Pooter:
				pActor = CreateActor<Pooter>();
				break;
			case LogicValue::EditorActorType::Boomfly:
				pActor = CreateActor<Boomfly>();
				break;
			case LogicValue::EditorActorType::full_fly:
				pActor = CreateActor<full_fly>();
				break;
			case LogicValue::EditorActorType::Deathshead:
				pActor = CreateActor<Deathshead>();
				break;
			case LogicValue::EditorActorType::Nerveending:
				pActor = CreateActor<Nerveending>();
				break;
			case LogicValue::EditorActorType::Psychicmaw:
				pActor = CreateActor<Psychicmaw>();
				break;
			case LogicValue::EditorActorType::Psychic_horf:
				pActor = CreateActor<Psychic_horf>();
				break;
			case LogicValue::EditorActorType::Onetooth:
				pActor = CreateActor<Onetooth>();
				break;
			case LogicValue::EditorActorType::Redboomfly:
				pActor = CreateActor<Redboomfly>();
				break;
			case LogicValue::EditorActorType::Bomb:
				pActor = CreateActor<Bomb>();
				break;
			case LogicValue::EditorActorType::BonFire:
				pActor = CreateActor<BonFire>();
				break;
			case LogicValue::EditorActorType::Poop:
				pActor = CreateActor<Poop>();
				break;
			case LogicValue::EditorActorType::Stone:
				pActor = CreateActor<Stone>();
				break;
			case LogicValue::EditorActorType::Horf:
				pActor = CreateActor<Horf>();
				break;
			case LogicValue::EditorActorType::Dinga:
				pActor = CreateActor<Dinga>();
				break;
			case LogicValue::EditorActorType::Dip:
				pActor = CreateActor<Dip>();
				break;
			case LogicValue::EditorActorType::Host:
				pActor = CreateActor<Host>();
				break;
			case LogicValue::EditorActorType::Moms_hand:
				pActor = CreateActor<Moms_hand>();
				break;
			case LogicValue::EditorActorType::Redmaw:
				pActor = CreateActor<Redmaw>();
				break;
			case LogicValue::EditorActorType::Squirt:
				pActor = CreateActor<Squirt>();
				break;
			case LogicValue::EditorActorType::Sucker:
				pActor = CreateActor<Sucker>();
				break;
			case LogicValue::EditorActorType::Turret:
				pActor = CreateActor<Turret>();
				break;
			case LogicValue::EditorActorType::Spikes:
				pActor = CreateActor<Spikes>();
				break;
			case LogicValue::EditorActorType::PitLeftTop:
				pActor = CreateActor<PitLeftTop>();
				break;
			case LogicValue::EditorActorType::PitTop:
				pActor = CreateActor<PitTop>();
				break;
			case LogicValue::EditorActorType::PitRightTop:
				pActor = CreateActor<PitRightTop>();
				break;
			case LogicValue::EditorActorType::PitLeft:
				pActor = CreateActor<PitLeft>();
				break;
			case LogicValue::EditorActorType::PitCenter:
				pActor = CreateActor<PitCenter>();
				break;
			case LogicValue::EditorActorType::PitRight:
				pActor = CreateActor<PitRight>();
				break;
			case LogicValue::EditorActorType::PitLeftBottom:
				pActor = CreateActor<PitLeftBottom>();
				break;
			case LogicValue::EditorActorType::PitBottom:
				pActor = CreateActor<PitBottom>();
				break;
			case LogicValue::EditorActorType::PitRightBottom:
				pActor = CreateActor<PitRightBottom>();
				break;
			case LogicValue::EditorActorType::BoxItem:
				pActor = CreateActor<BoxItem>();
				break;
			case LogicValue::EditorActorType::MAX:
				break;
			default:
				break;
			}
			if (pActor == nullptr)
			{
				EngineDebug::AssertMsg("if (pActor == nullptr)");
			}
			pActor->SetPosition(MousePos);
			//pActor->SetSize({ 30.f,30.f });
			pActor->On();
			m_AllActor[SelectRoom].push_back(pActor);
		}
		
	}

	else if (EngineInput::IsPress(L"Remove"))
	{
		//만약 없으면 오류
		if (m_AllActor.end() == m_AllActor.find(SelectRoom))
		{
			EngineDebug::AssertMsg("if (m_AllActor.end() == m_AllActor.find(SelectRoom))");
		}

		std::list<EngineActor*>::iterator	iter = m_AllActor[SelectRoom].begin();
		std::list<EngineActor*>::iterator	iterEnd = m_AllActor[SelectRoom].end();
		
		for (; iter != iterEnd;)
		{
			float4 Pos = (*iter)->GetPosition();
			float4 Size = (*iter)->GetSize();
			float4 MousePos = EngineWindow::MousePos();
			if (MousePos.ix() < Pos.ix() - Size.ihx() || MousePos.ix() > Pos.ix() + Size.ihx())
			{
				++iter;
				continue;
			}

			if (MousePos.iy() <= Pos.iy() - Size.ihy() || MousePos.iy() >= Pos.iy() + Size.ihy())
			{
				++iter;
				continue;
			}

			
			(*iter)->Death();
			iter= m_AllActor[SelectRoom].erase(iter);
			iterEnd = m_AllActor[SelectRoom].end();
		}
	}
	if (EngineInput::IsUp(L"Prev"))
	{
		int num = static_cast<int>(SelectActor) - 1;
		if (num < 0) 
		{
			num = static_cast<int>(LogicValue::EditorActorType::MAX)-1;
		}
		SelectActor = (LogicValue::EditorActorType)num;
	}
	if (EngineInput::IsUp(L"Next"))
	{
		int num = static_cast<int>(SelectActor) + 1;
		if (num == static_cast<int>(LogicValue::EditorActorType::MAX))
		{
			num = 0;
		}
		SelectActor = (LogicValue::EditorActorType)num;
	}

}

void RoomEditor::SceneDebugRender()
{
	float4 MousePos = EngineWindow::MousePos();

	int posy = 10;
	EngineString PrintText = L"MousePos";
	PrintText += L" X ";
	PrintText += MousePos.ix();
	PrintText += L" Y ";
	PrintText += MousePos.iy();
	DebugTextout(PrintText, 10, posy);

	posy += 40;
	PrintText = L"SelectRoom : ";
	switch (SelectRoom)
	{
	case LogicValue::RoomInfoGroup::Room1:
		PrintText += L"Room1";
		break;
	case LogicValue::RoomInfoGroup::Room2:
		PrintText += L"Room2";
		break;
	case LogicValue::RoomInfoGroup::Room3:
		PrintText += L"Room3";
		break;
	case LogicValue::RoomInfoGroup::Room4:
		PrintText += L"Room4";
		break;
	case LogicValue::RoomInfoGroup::Room5:
		PrintText += L"Room5";
		break;
	case LogicValue::RoomInfoGroup::Room6:
		PrintText += L"Room6";
		break;
	case LogicValue::RoomInfoGroup::Room7:
		PrintText += L"Room7";
		break;
	case LogicValue::RoomInfoGroup::Room8:
		PrintText += L"Room8";
		break;
	case LogicValue::RoomInfoGroup::Room9:
		PrintText += L"Room9";
		break;
	case LogicValue::RoomInfoGroup::Room10:
		PrintText += L"Room10";
		break;
	case LogicValue::RoomInfoGroup::Room11:
		PrintText += L"Room11";
		break;
	case LogicValue::RoomInfoGroup::Room12:
		PrintText += L"Room12";
		break;
	case LogicValue::RoomInfoGroup::Room13:
		PrintText += L"Room13";
		break;
	case LogicValue::RoomInfoGroup::NotEnemyRoom1:
		PrintText += L"NotEnemyRoom1";
		break;
	case LogicValue::RoomInfoGroup::NotEnemyRoom2:
		PrintText += L"NotEnemyRoom2";
		break;
	}

	DebugTextout(PrintText, 10, posy);
	posy += 40;
	PrintText = L"Save : Ctrl+S";
	DebugTextout(PrintText, 10, posy);
	posy += 40;
	PrintText = L"Load : Ctrl+L";
	DebugTextout(PrintText, 10, posy);
	posy += 40;
	PrintText = L"Prev : Z";
	DebugTextout(PrintText, 10, posy);
	posy += 40;
	PrintText = L"Next : C";
	DebugTextout(PrintText, 10, posy);
	posy += 40;
	PrintText = L"RoomPrev : A";
	DebugTextout(PrintText, 10, posy);
	posy += 40;
	PrintText = L"RoomNext : D";
	DebugTextout(PrintText, 10, posy);
	posy += 40;
}

void RoomEditor::Save()
{
	EngineFile	pFile;

	pFile.m_Str = L"..\\Res\\Data\\RoomEnemyType\\RoomEnemyInfo.data";
	pFile.Open(L"wb");
	
	//모든 방 저장
	std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::iterator Start = m_AllActor.begin();
	std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::iterator End = m_AllActor.end();

	for (; Start != End; ++Start)
	{
		//첫번째방부터
		std::list<EngineActor*>& _RoomAllActor = Start->second;
		std::list<EngineActor*>::iterator	iter = _RoomAllActor.begin();
		std::list<EngineActor*>::iterator	iterEnd = _RoomAllActor.end();

		// 오브젝트개수저장
		int Size = static_cast<int>(_RoomAllActor.size());
		pFile.Write(&Size, sizeof(int), 1);

		for (; iter != iterEnd; ++iter)
		{
			EngineString str = (*iter)->GetClassType();
			LogicValue::EditorActorType type = LogicValue::EditorActorType::MAX;
			{
				if (str == L"Fly")
				{
					type = LogicValue::EditorActorType::Fly;
				}
				if (str == L"Pooter")
				{
					type = LogicValue::EditorActorType::Pooter;
				}

				if (str == L"Boomfly")
				{
					type = LogicValue::EditorActorType::Boomfly;
				}
				if (str == L"full_fly")
				{
					type = LogicValue::EditorActorType::full_fly;
				}
				if (str == L"Deathshead")
				{
					type = LogicValue::EditorActorType::Deathshead;
				}
				if (str == L"Nerveending")
				{
					type = LogicValue::EditorActorType::Nerveending;
				}
				if (str == L"Psychicmaw")
				{
					type = LogicValue::EditorActorType::Psychicmaw;
				}
				if (str == L"Psychic_horf")
				{
					type = LogicValue::EditorActorType::Psychic_horf;
				}
				if (str == L"Onetooth")
				{
					type = LogicValue::EditorActorType::Onetooth;
				}
				if (str == L"Redboomfly")
				{
					type = LogicValue::EditorActorType::Redboomfly;
				}
				if (str == L"Bomb")
				{
					type = LogicValue::EditorActorType::Bomb;
				}
				if (str == L"BonFire")
				{
					type = LogicValue::EditorActorType::BonFire;
				}
				if (str == L"Poop")
				{
					type = LogicValue::EditorActorType::Poop;
				}
				if (str == L"Stone")
				{
					type = LogicValue::EditorActorType::Stone;
				}
				if (str == L"Horf")
				{
					type = LogicValue::EditorActorType::Horf;
				}
				if (str == L"Dinga")
				{
					type = LogicValue::EditorActorType::Dinga;
				}

				if (str == L"Dip")
				{
					type = LogicValue::EditorActorType::Dip;
				}
				if (str == L"Host")
				{
					type = LogicValue::EditorActorType::Host;
				}

				if (str == L"Moms_hand")
				{
					type = LogicValue::EditorActorType::Moms_hand;
				}
				if (str == L"Redmaw")
				{
					type = LogicValue::EditorActorType::Redmaw;
				}

				if (str == L"Squirt")
				{
					type = LogicValue::EditorActorType::Squirt;
				}
				if (str == L"Sucker")
				{
					type = LogicValue::EditorActorType::Sucker;
				}
				if (str == L"Turret")
				{
					type = LogicValue::EditorActorType::Turret;
				}

				if (str == L"Spikes")
				{
					type = LogicValue::EditorActorType::Spikes;
				}
				if (str == L"PitLeftTop")
				{
					type = LogicValue::EditorActorType::PitLeftTop;
				}
				if (str == L"PitTop")
				{
					type = LogicValue::EditorActorType::PitTop;
				}
				if (str == L"PitRightTop")
				{
					type = LogicValue::EditorActorType::PitRightTop;
				}
				if (str == L"PitLeft")
				{
					type = LogicValue::EditorActorType::PitLeft;
				}
				if (str == L"PitCenter")
				{
					type = LogicValue::EditorActorType::PitCenter;
				}
				if (str == L"PitRight")
				{
					type = LogicValue::EditorActorType::PitRight;
				}
				if (str == L"PitLeftBottom")
				{
					type = LogicValue::EditorActorType::PitLeftBottom;
				}
				if (str == L"PitBottom")
				{
					type = LogicValue::EditorActorType::PitBottom;
				}
				if (str == L"PitRightBottom")
				{
					type = LogicValue::EditorActorType::PitRightBottom;
				}
				if (str == L"BoxItem")
				{
					type = LogicValue::EditorActorType::BoxItem;
				}
			}
			if (type == LogicValue::EditorActorType::MAX) //에디터액터아님
			{
				continue;
			}
			int itype = static_cast<int>(type);
			pFile.Write(&itype, sizeof(int), 1);
			float4 pos = (*iter)->GetPosition();
			pFile.Write(&pos, sizeof(float4), 1);
		}

	}

	pFile.Close();
}

void RoomEditor::Load()
{
	EngineFile	pFile;

	pFile.m_Str = L"..\\Res\\Data\\RoomEnemyType\\RoomEnemyInfo.data";
	pFile.Open(L"rb");

	//방갯수는 이미 정해져있다.
	//로드시 기존 모든것 클리어하기
	std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::iterator Start = m_AllActor.begin();
	std::map<LogicValue::RoomInfoGroup, std::list<EngineActor*>>::iterator End = m_AllActor.end();

	for (; Start != End; ++Start)
	{
		//첫번째방부터
		std::list<EngineActor*>& _RoomAllActor = Start->second;
		std::list<EngineActor*>::iterator	iter = _RoomAllActor.begin();
		std::list<EngineActor*>::iterator	iterEnd = _RoomAllActor.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Death();
		}
		_RoomAllActor.clear();
	}

	//방은 이미 다 생성했으므로 다 남아있음 바로불러오기
	for (int RoomGroup = 0; RoomGroup < static_cast<int>(LogicValue::RoomInfoGroup::Max); ++RoomGroup)
	{
		int Size = 0;
		pFile.Read(&Size, sizeof(int), sizeof(int), 1);

		for (int i = 0; i < Size; ++i)
		{
			int itype = 99;
			pFile.Read(&itype, sizeof(int), sizeof(int), 1);

			float4 pos;
			pFile.Read(&pos, sizeof(float4), sizeof(float4), 1);
			if (itype == 99)
			{
				EngineDebug::AssertMsg("if (itype == 99)");
			}

			LogicValue::EditorActorType type = (LogicValue::EditorActorType)itype;

			EngineActor* pActor = nullptr;

			switch (type)
			{
			case LogicValue::EditorActorType::Fly:
				pActor = CreateActor<Fly>();
				break;
			case LogicValue::EditorActorType::Pooter:
				pActor = CreateActor<Pooter>();
				break;
			case LogicValue::EditorActorType::Boomfly:
				pActor = CreateActor<Boomfly>();
				break;
			case LogicValue::EditorActorType::full_fly:
				pActor = CreateActor<full_fly>();
				break;
			case LogicValue::EditorActorType::Deathshead:
				pActor = CreateActor<Deathshead>();
				break;
			case LogicValue::EditorActorType::Nerveending:
				pActor = CreateActor<Nerveending>();
				break;
			case LogicValue::EditorActorType::Psychicmaw:
				pActor = CreateActor<Psychicmaw>();
				break;
			case LogicValue::EditorActorType::Psychic_horf:
				pActor = CreateActor<Psychic_horf>();
				break;
			case LogicValue::EditorActorType::Onetooth:
				pActor = CreateActor<Onetooth>();
				break;
			case LogicValue::EditorActorType::Redboomfly:
				pActor = CreateActor<Redboomfly>();
				break;
			case LogicValue::EditorActorType::Bomb:
				pActor = CreateActor<Bomb>();
				break;
			case LogicValue::EditorActorType::BonFire:
				pActor = CreateActor<BonFire>();
				break;
			case LogicValue::EditorActorType::Poop:
				pActor = CreateActor<Poop>();
				break;
			case LogicValue::EditorActorType::Stone:
				pActor = CreateActor<Stone>();
				break;
			case LogicValue::EditorActorType::Horf:
				pActor = CreateActor<Horf>();
				break;
			case LogicValue::EditorActorType::Dinga:
				pActor = CreateActor<Dinga>();
				break;
			case LogicValue::EditorActorType::Dip:
				pActor = CreateActor<Dip>();
				break;
			case LogicValue::EditorActorType::Host:
				pActor = CreateActor<Host>();
				break;
			case LogicValue::EditorActorType::Moms_hand:
				pActor = CreateActor<Moms_hand>();
				break;
			case LogicValue::EditorActorType::Redmaw:
				pActor = CreateActor<Redmaw>();
				break;
			case LogicValue::EditorActorType::Squirt:
				pActor = CreateActor<Squirt>();
				break;
			case LogicValue::EditorActorType::Sucker:
				pActor = CreateActor<Sucker>();
				break;
			case LogicValue::EditorActorType::Turret:
				pActor = CreateActor<Turret>();
				break;


			case LogicValue::EditorActorType::Spikes:
				pActor = CreateActor<Spikes>();
				break;
			case LogicValue::EditorActorType::PitLeftTop:
				pActor = CreateActor<PitLeftTop>();
				break;
			case LogicValue::EditorActorType::PitTop:
				pActor = CreateActor<PitTop>();
				break;
			case LogicValue::EditorActorType::PitRightTop:
				pActor = CreateActor<PitRightTop>();
				break;
			case LogicValue::EditorActorType::PitLeft:
				pActor = CreateActor<PitLeft>();
				break;
			case LogicValue::EditorActorType::PitCenter:
				pActor = CreateActor<PitCenter>();
				break;
			case LogicValue::EditorActorType::PitRight:
				pActor = CreateActor<PitRight>();
				break;
			case LogicValue::EditorActorType::PitLeftBottom:
				pActor = CreateActor<PitLeftBottom>();
				break;
			case LogicValue::EditorActorType::PitBottom:
				pActor = CreateActor<PitBottom>();
				break;
			case LogicValue::EditorActorType::PitRightBottom:
				pActor = CreateActor<PitRightBottom>();
				break;
			case LogicValue::EditorActorType::BoxItem:
				pActor = CreateActor<BoxItem>();
				break;
			case LogicValue::EditorActorType::MAX:
				EngineDebug::AssertMsg("case LogicValue::EditorActorType::MAX");
				break;
			default:
				break;
			}
			if (pActor == nullptr)
			{
				EngineDebug::AssertMsg("if (pActor == nullptr)");
			}
			pActor->SetPosition(pos);
			pActor->SetSize({ 30.f,30.f });
			pActor->On();
			m_AllActor[(LogicValue::RoomInfoGroup)RoomGroup].push_back(pActor);

		}
	}

	

	pFile.Close();
}
