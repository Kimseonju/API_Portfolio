#pragma once
#include <EngineScene.h>
#include "LogicValue.h"
//용도 :
//설명 :
class Enemy;

class RoomEditor : public EngineScene
{
private: //static
public:  //static func
private: 
public: //member

	//맵에 깔린 모든 오브젝트
	std::map<LogicValue::RoomInfoGroup ,std::list<EngineActor*>> m_AllActor;

	//선택된 오브젝트 액터
	std::vector<EngineActor*> m_UIActor;

	//선택된 번호(오브젝트)
	LogicValue::EditorActorType SelectActor;

	//선택된 방
	LogicValue::RoomInfoGroup SelectRoom;
public: //constructer destructer
	RoomEditor();
	~RoomEditor();

public: 
	RoomEditor(const RoomEditor& _Other) = delete;
	RoomEditor(const RoomEditor&& _Other) = delete;

public:
	RoomEditor& operator=(const RoomEditor& _Other) = delete;
	RoomEditor& operator=(const RoomEditor&& _Other) = delete;

public: //member
	void Start() override;
	void SceneUpdate() override;
	void SceneDebugRender() override;

public:
	void Save();
	void Load();
};

