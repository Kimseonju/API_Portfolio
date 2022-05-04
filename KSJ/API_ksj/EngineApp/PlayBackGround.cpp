#include "PlayBackGround.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
//static
//static func

int PlayBackGround::iRoomImageNumber = 0;
PlayBackGround::PlayBackGround():NewRenderer(nullptr)
{
}

PlayBackGround::~PlayBackGround()
{
}

void PlayBackGround::Init(LogicValue::RoomType _Type, const float4& m_MapCount)
{
	float4 MapSize = EngineWindow::GetSize();
	SetPosition({ (MapSize.ix() * (m_MapCount.ix())) + MapSize.ihx(), (MapSize.iy() * (m_MapCount.iy())) + MapSize.ihy() });

	//¸Ê¹è°æ 
	if (LogicValue::RoomType::Boss == _Type)
	{
		NewRenderer->BltCut_Setting(L"Baseboss.bmp", 0);
	}
	else if (LogicValue::RoomType::Room == _Type)
	{
		if (static_cast<int>(LogicValue::RoomImageGroup::Basement1) == iRoomImageNumber)
		{
			NewRenderer->BltCut_Setting(L"Basement1.bmp", 0);

		}
		else if (static_cast<int>(LogicValue::RoomImageGroup::Basement2 )== iRoomImageNumber)
		{
			NewRenderer->BltCut_Setting(L"Basement2.bmp", 0);

		}
		else if (static_cast<int>(LogicValue::RoomImageGroup::Basement3) == iRoomImageNumber)
		{
			NewRenderer->BltCut_Setting(L"Basement3.bmp", 0);

		}

		else if (static_cast<int>(LogicValue::RoomImageGroup::Basement4) == iRoomImageNumber)
		{
			NewRenderer->BltCut_Setting(L"Basement4.bmp", 0);

		}

		else if (static_cast<int>(LogicValue::RoomImageGroup::Basement5 )== iRoomImageNumber)
		{
			NewRenderer->BltCut_Setting(L"Basement5.bmp", 0);

		}
		NextRoomImage();
	}
	else if (LogicValue::RoomType::Shop == _Type)
	{
		//ÀÌµû°¡ »óÁ¡¸Ê¹è°æ±ò±â
		NewRenderer->BltCut_Setting(L"Basement1.bmp", 0);
	}
	else if (LogicValue::RoomType::Secret == _Type)
	{
		NewRenderer->BltCut_Setting(L"BaseSecret.bmp",0);
	}
	else if (LogicValue::RoomType::Treasure == _Type)
	{
		NewRenderer->BltCut_Setting(L"Treasure.bmp", 0);
	}
	else if (LogicValue::RoomType::FinalBoss == _Type)
	{
		NewRenderer->BltCut_Setting(L"BaseMomBoss.bmp", 0);
	}
	else
	{
		EngineDebug::AssertMsg("else");
	}
}

void PlayBackGround::Start()
{
	NewRenderer = CreateRenderer<EngineRendererBasic>(0);
}

void PlayBackGround::Update()
{

}
