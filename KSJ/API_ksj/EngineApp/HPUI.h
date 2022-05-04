#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
//용도 :
//설명 : 플레이어가져와서 하트그리기
class EngineRendererBasic;
class HPUI : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member
	std::list<EngineRendererBasic*>m_MapRender;
	
public: //constructer destructer
	HPUI();
	~HPUI();

public: 
	HPUI(const HPUI& _Other) = delete;
	HPUI(const HPUI&& _Other) = delete;

public:
	HPUI& operator=(const HPUI& _Other) = delete;
	HPUI& operator=(const HPUI&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
};

