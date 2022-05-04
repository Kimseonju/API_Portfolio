#pragma once
#include <EngineActor.h>
#include <EngineTimeEventer.h>

//�뵵 :
//���� : SelectScene���ö� FadeIn  ����ϱ� (�״�� PlayScene���� �ѱ��)
class EngineRendererBasic;
class SelectFadeIn : public EngineActor
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererBasic* m_Render;
	EngineRendererBasic* m_RenderIcon;
	float Alpha;


	EngineTimeEventer<SelectFadeIn> FadeOutTimer;

public: //constructer destructer
	SelectFadeIn();
	~SelectFadeIn();

public:
	SelectFadeIn(const SelectFadeIn& _Other) = delete;
	SelectFadeIn(const SelectFadeIn&& _Other) = delete;

public:
	SelectFadeIn& operator=(const SelectFadeIn& _Other) = delete;
	SelectFadeIn& operator=(const SelectFadeIn&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;

	void FadeOutStart();
	void FadeOut();
	void FadeOutEnd();
};
