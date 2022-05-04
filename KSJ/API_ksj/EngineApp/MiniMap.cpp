#include "MiniMap.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
//static
//static func


MiniMap::MiniMap() : m_MapSize(float4::ZERO), m_SelectRender(nullptr)
{
	memset(m_Map, 0, sizeof(m_Map));
}

MiniMap::~MiniMap()
{
}

void MiniMap::Start()
{
	EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
	NewRenderer->TransSetting(L"MiniMapBackground.bmp", { 128, 96 });
	NewRenderer->SetPivotPos(float4(800.f, 30.f));
	NewRenderer->CamPosOff();
	NewRenderer->TransNotCenter();

	m_SelectRender= CreateRenderer<EngineRendererBasic>(4);
	m_SelectRender->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 0);
	m_SelectRender->SetPivotPos(float4(800.f + (16.f * 2.f), 30.f + (16.f * 2.f)));
	m_SelectRender->CamPosOff();
	NewRenderer->TransNotCenter();
}

void MiniMap::MapResize(const float4& _MapCount)
{
	memset(m_Map, 0, sizeof(m_Map));

}

void MiniMap::InputMapRender(const float4& _MapCount, LogicValue::RoomType _Type)
{
	if (m_Map[_MapCount.iy()][_MapCount.ix()])
	{
		return;
	}
	switch (_Type)
	{
		EngineRendererBasic* NewRenderer;
	case LogicValue::RoomType::Boss:
	case LogicValue::RoomType::FinalBoss:
		NewRenderer = CreateRenderer<EngineRendererBasic>(2);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 1);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();

		NewRenderer = CreateRenderer<EngineRendererBasic>(3);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 5);
		NewRenderer->SetPivotPos(float4(800.f +(16.f * _MapCount.x), 30.f+(16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();
		break;

	case LogicValue::RoomType::Room:
		NewRenderer = CreateRenderer<EngineRendererBasic>(2);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 1);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();
		break;

	case LogicValue::RoomType::Secret:
		NewRenderer = CreateRenderer<EngineRendererBasic>(2);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 1);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();

		NewRenderer = CreateRenderer<EngineRendererBasic>(3);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 4);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();
		break;

	case LogicValue::RoomType::Treasure:
		NewRenderer = CreateRenderer<EngineRendererBasic>(2);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 1);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();

		NewRenderer = CreateRenderer<EngineRendererBasic>(3);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 3);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();
		break;
	case LogicValue::RoomType::Shop:
		NewRenderer = CreateRenderer<EngineRendererBasic>(2);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 1);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();

		NewRenderer = CreateRenderer<EngineRendererBasic>(3);
		NewRenderer->TransCut_NotCenterSetting(L"MiniMapIcon.bmp", 2);
		NewRenderer->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
		NewRenderer->CamPosOff();
		NewRenderer->TransNotCenter();
		break;
	}
	m_Map[_MapCount.iy()][_MapCount.ix()] = true;
}

void MiniMap::MoveMapRender(const float4& _MapCount)
{
	m_SelectRender->SetPivotPos(float4(800.f + (16.f * _MapCount.x), 30.f + (16.f * _MapCount.y)));
}

void MiniMap::DebugRender()
{

}

