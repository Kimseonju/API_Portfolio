#pragma once
#include <EngineActor.h>
#include <EngineTimeEventer.h>
//�뵵 :
//���� : PlayScene���ö� FadeInOut ����ϱ�
//�ٸ��� �̵��Ҷ��� ���(����)
class EngineRendererBasic;
class FadeActor : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member
	EngineRendererBasic* m_Render;
	float Alpha;


	EngineTimeEventer<FadeActor> FadeInTimer;
	EngineTimeEventer<FadeActor> FadeOutTimer;

public: //constructer destructer
	FadeActor();
	~FadeActor();

public: 
	FadeActor(const FadeActor& _Other) = delete;
	FadeActor(const FadeActor&& _Other) = delete;

public:
	FadeActor& operator=(const FadeActor& _Other) = delete;
	FadeActor& operator=(const FadeActor&& _Other) = delete;

public: //member
	void Start() override; 
	void Update() override; 

	void FadeInStart();
	void FadeIn();
	void FadeInEnd();


	void FadeOutStart();
	void FadeOut();
	void FadeOutEnd();
};

