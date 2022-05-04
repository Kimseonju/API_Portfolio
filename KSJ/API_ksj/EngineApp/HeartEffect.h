#pragma once
#include <EngineActor.h>

//용도 :
//설명 : HPMAX 가 올라갔을때
class EngineRendererAnim;
class HeartEffect : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member

	EngineRendererAnim* m_RenderBody;

public: //constructer destructer
	HeartEffect();
	~HeartEffect();

public: 
	HeartEffect(const HeartEffect& _Other) = delete;
	HeartEffect(const HeartEffect&& _Other) = delete;

public:
	HeartEffect& operator=(const HeartEffect& _Other) = delete;
	HeartEffect& operator=(const HeartEffect&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
};

