#pragma once
#include <EngineActor.h>

//용도 :
//설명 :
class EngineRendererBasic;
class RoomEditorBackground : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member



public: //constructer destructer
	RoomEditorBackground();
	~RoomEditorBackground();

public: 
	RoomEditorBackground(const RoomEditorBackground& _Other) = delete;
	RoomEditorBackground(const RoomEditorBackground&& _Other) = delete;

public:
	RoomEditorBackground& operator=(const RoomEditorBackground& _Other) = delete;
	RoomEditorBackground& operator=(const RoomEditorBackground&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
public:
};

