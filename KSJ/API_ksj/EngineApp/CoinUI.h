#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
//�뵵 :
//���� : �÷��̾���ͼ� ����
class EngineRendererBasic;
class CoinUI : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererBasic* m_TenRender;
	EngineRendererBasic* m_OneRender;
public: //constructer destructer
	CoinUI();
	~CoinUI();

public:
	CoinUI(const CoinUI& _Other) = delete;
	CoinUI(const CoinUI&& _Other) = delete;

public:
	CoinUI& operator=(const CoinUI& _Other) = delete;
	CoinUI& operator=(const CoinUI&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
};

