#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
//용도 :
//설명 :
class EngineRendererBasic;
class PlayBackGround : public EngineActor
{
private: //static
	static int iRoomImageNumber;

	static void NextRoomImage()
	{
		iRoomImageNumber++;
		
		if (iRoomImageNumber == static_cast<int>(LogicValue::RoomImageGroup::Max))
		{
			iRoomImageNumber = 0;
		}
	}
public:  //static func
private: 
public: //member


	EngineRendererBasic* NewRenderer;

public: //constructer destructer
	PlayBackGround();
	~PlayBackGround();

public: 
	PlayBackGround(const PlayBackGround& _Other) = delete;
	PlayBackGround(const PlayBackGround&& _Other) = delete;

public:
	PlayBackGround& operator=(const PlayBackGround& _Other) = delete;
	PlayBackGround& operator=(const PlayBackGround&& _Other) = delete;

public: //member
	void Init(LogicValue::RoomType _Type, const float4& m_MapCount);
	void Start() override;
	void Update() override;
	
};

