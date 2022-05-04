#pragma once
#include <EngineScene.h>
#include "LogicValue.h"
//�뵵 :
//���� :
class Enemy;

class RoomEditor : public EngineScene
{
private: //static
public:  //static func
private: 
public: //member

	//�ʿ� �� ��� ������Ʈ
	std::map<LogicValue::RoomInfoGroup ,std::list<EngineActor*>> m_AllActor;

	//���õ� ������Ʈ ����
	std::vector<EngineActor*> m_UIActor;

	//���õ� ��ȣ(������Ʈ)
	LogicValue::EditorActorType SelectActor;

	//���õ� ��
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

