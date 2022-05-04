#pragma once
#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <EngineDebug.h>
class EngineRendererBasic;
class RoomInfo;
class ItemEffect : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererBasic* m_ItemUIEffect;
	float Alpha;
	float m_TimeSize;
	float m_Timer;
	float m_MoveTimer;
	float m_Move;
	RoomInfo* m_Room;
public: //constructer destructer
	ItemEffect();
	~ItemEffect();

public:
	ItemEffect(const ItemEffect& _Other) = delete;
	ItemEffect(const ItemEffect&& _Other) = delete;

public:
	ItemEffect& operator=(const ItemEffect& _Other) = delete;
	ItemEffect& operator=(const ItemEffect&& _Other) = delete;

public: //member
	void Start() override;
	void UpdateUI() override;

	void FadeOutStart();
	void FadeOut();
	void FadeOutEnd();

	void SetRoom(RoomInfo* _Room)
	{
		m_Room = _Room;
	}
};


