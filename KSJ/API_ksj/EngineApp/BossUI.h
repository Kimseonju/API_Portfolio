#pragma once
#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <EngineDebug.h>
class EngineRendererBasic;
class BossUI : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererBasic* m_BossHPRender;
	EngineRendererBasic* m_BossHPLayer;

public: //constructer destructer
	BossUI();
	~BossUI();

public:
	BossUI(const BossUI& _Other) = delete;
	BossUI(const BossUI&& _Other) = delete;

public:
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(const BossUI&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;

	void SetPercentBar(float _Percent);

};


