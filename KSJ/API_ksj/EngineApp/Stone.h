#pragma once

#include <EngineActor.h>

class EngineRendererAnim;
class EngineRendererBasic;
//용도 :
//설명 :
class Stone : public EngineActor
{
private: //static
public:  //static func
private: 
	EngineCollision* m_Collision;
	EngineRendererBasic* m_RenderBody;
public: //member



public: //constructer destructer
	Stone();
	~Stone();

public: 
	Stone(const Stone& _Other) = delete;
	Stone(const Stone&& _Other) = delete;

public:
	Stone& operator=(const Stone& _Other) = delete;
	Stone& operator=(const Stone&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void DebugRender() override;

public:

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

