#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
//¿ëµµ :
//¼³¸í : ¿­¼è°¹¼ö
class EngineRendererBasic;
class KeyUI : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererBasic* m_TenRender;
	EngineRendererBasic* m_OneRender;
public: //constructer destructer
	KeyUI();
	~KeyUI();

public:
	KeyUI(const KeyUI& _Other) = delete;
	KeyUI(const KeyUI&& _Other) = delete;

public:
	KeyUI& operator=(const KeyUI& _Other) = delete;
	KeyUI& operator=(const KeyUI&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
};

