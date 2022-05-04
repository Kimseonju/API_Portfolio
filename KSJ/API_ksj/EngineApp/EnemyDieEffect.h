#pragma once
#include <EngineActor.h>

class EngineRendererAnim;
class EngineRendererBasic;

//용도 :
//설명 :
class EnemyDieEffect : public EngineActor
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererAnim* m_RenderEffect;
	float m_time;
public: //constructer destructer
	EnemyDieEffect();
	~EnemyDieEffect();

public:
	EnemyDieEffect(const EnemyDieEffect& _Other) = delete;
	EnemyDieEffect(const EnemyDieEffect&& _Other) = delete;

public:
	EnemyDieEffect& operator=(const EnemyDieEffect& _Other) = delete;
	EnemyDieEffect& operator=(const EnemyDieEffect&& _Other) = delete;

public:
	// member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;
	void SelectPoop();
};

