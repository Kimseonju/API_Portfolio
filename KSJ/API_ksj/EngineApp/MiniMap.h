#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#define MapX 6
#define MapY 6

//용도 :
//설명 :
class EngineRendererBasic;
class MiniMap : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member

	std::list<EngineRendererBasic*>m_MapRender;
	EngineRendererBasic* m_SelectRender;
	bool m_Map[MapY][MapX];
	float4 m_MapSize;
public: //constructer destructer
	MiniMap();
	~MiniMap();

public: 
	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(const MiniMap&& _Other) = delete;

public:
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(const MiniMap&& _Other) = delete;

public: //member
	void Start() override;
	void MapResize(const float4& _MapCount);
	void InputMapRender(const float4& _MapCount, LogicValue::RoomType _Type);
	void MoveMapRender(const float4& _MapCount);
	void DebugRender() override;

};

