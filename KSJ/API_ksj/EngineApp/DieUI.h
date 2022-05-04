#pragma once
#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <EngineDebug.h>
class EngineRendererBasic;
class RoomInfo;
class DieUI : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererBasic* m_DieBackground;
	EngineRendererBasic* m_DieEnemyImage;

	RoomInfo* m_Room;
public: //constructer destructer
	DieUI();
	~DieUI();

public:
	DieUI(const DieUI& _Other) = delete;
	DieUI(const DieUI&& _Other) = delete;

public:
	DieUI& operator=(const DieUI& _Other) = delete;
	DieUI& operator=(const DieUI&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void UpdateUI() override;
	void SetDieEnemyImage(const EngineString& _EnemyStr);
	void SetRoomInfo(RoomInfo* _Room)
	{
		m_Room = _Room;
	}
};


