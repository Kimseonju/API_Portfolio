#pragma once
#include <EngineActor.h>
#include <EngineTimeEventer.h>

//용도 :
//설명 : 처음시작했을때 FadeOut 하는것
class EngineRendererBasic;
class PlayFadeOut : public EngineActor
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererBasic* m_Render;
	EngineRendererBasic* m_RenderIcon;
	float Alpha;

	EngineTimeEventer<PlayFadeOut> FadeOutTimer;

public: //constructer destructer
	PlayFadeOut();
	~PlayFadeOut();

public:
	PlayFadeOut(const PlayFadeOut& _Other) = delete;
	PlayFadeOut(const PlayFadeOut&& _Other) = delete;

public:
	PlayFadeOut& operator=(const PlayFadeOut& _Other) = delete;
	PlayFadeOut& operator=(const PlayFadeOut&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;

	void FadeOutStart();
	void FadeOut();
	void FadeOutEnd();
};
