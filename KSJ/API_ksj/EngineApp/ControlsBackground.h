#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
//용도 :
//설명 :
class EngineRendererBasic;
class ControlsBackground : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member


	EngineRendererBasic* NewRenderer;

public: //constructer destructer
	ControlsBackground();
	~ControlsBackground();

public: 
	ControlsBackground(const ControlsBackground& _Other) = delete;
	ControlsBackground(const ControlsBackground&& _Other) = delete;

public:
	ControlsBackground& operator=(const ControlsBackground& _Other) = delete;
	ControlsBackground& operator=(const ControlsBackground&& _Other) = delete;

public: //member
	void Init(const float4& m_MapCount);
	void Start() override;
	void Update() override;
	
};

