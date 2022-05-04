#pragma once
#include <EngineScene.h>

//�뵵 : �׽�Ʈ��
//���� : ������ ������ �ִϸ��̼� �׽�Ʈ �뵵
//
class EngineRendererBasic;
class TestScene : public EngineScene
{
private: //static
public:  //static func
private: 
public: //member
	EngineRendererBasic* m_Player; 
	EngineRendererBasic* m_PlayerSpot;
	EngineRendererBasic* m_PlayerText;

	EngineRendererBasic* m_VS;

	EngineRendererBasic* m_BossText;
	EngineRendererBasic* m_Boss;
	EngineRendererBasic* m_BossSpot;

public: //constructer destructer
	TestScene();
	~TestScene();

public: 
	TestScene(const TestScene& _Other) = delete;
	TestScene(const TestScene&& _Other) = delete;

public:
	TestScene& operator=(const TestScene& _Other) = delete;
	TestScene& operator=(const TestScene&& _Other) = delete;

public: //member
	void Start() override;
	void SceneUpdate() override;
};

