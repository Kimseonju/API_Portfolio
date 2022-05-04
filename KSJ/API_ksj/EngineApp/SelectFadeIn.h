#pragma once
#include <EngineActor.h>
#include <EngineTimeEventer.h>

//용도 :
//설명 : SelectScene나올때 FadeIn  사용하기 (그대로 PlayScene으로 넘기기)
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
