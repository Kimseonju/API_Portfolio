#pragma once
#include <EngineActor.h>

class EngineRendererAnim;
class EngineRendererBasic;

//용도 :
//설명 :
class PoofEffect : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererAnim* m_RenderEffect;

public: //constructer destructer
	PoofEffect();
	~PoofEffect();

public:
	PoofEffect(const PoofEffect& _Other) = delete;
	PoofEffect(const PoofEffect&& _Other) = delete;

public:
	PoofEffect& operator=(const PoofEffect& _Other) = delete;
	PoofEffect& operator=(const PoofEffect&& _Other) = delete;

public:
	// member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;
	void FireObject();
};

