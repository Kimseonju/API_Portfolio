#pragma once
#include <EngineActor.h>
#include "LogicValue.h"

class EngineRendererBasic;
class BombUI : public EngineActor
{
private: //static
public:  //static func
private:
public: //member
	EngineRendererBasic* m_TenRender;
	EngineRendererBasic* m_OneRender;
public: //constructer destructer
	BombUI();
	~BombUI();

public:
	BombUI(const BombUI& _Other) = delete;
	BombUI(const BombUI&& _Other) = delete;

public:
	BombUI& operator=(const BombUI& _Other) = delete;
	BombUI& operator=(const BombUI&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
};

