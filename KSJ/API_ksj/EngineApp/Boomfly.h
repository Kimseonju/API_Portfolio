#pragma once
#include "Enemy.h"
//용도 :
//설명 : 대각선으로 움직이다가 죽으면 폭발
class EngineCollision;
class Boomfly : public Enemy
{
private: // Static Var
public: // Static Boomfly
private: // member Var

	EngineCollision* m_Collision;
	float4 m_Dir;
public: //constructer destructer
	Boomfly();
	~Boomfly();

public:
	Boomfly(const Boomfly& _Other) = delete;
	Boomfly(const Boomfly&& _Other) = delete;

public:
	Boomfly& operator=(const Boomfly& _Other) = delete;
	Boomfly& operator=(const Boomfly&& _Other) = delete;

public: // member Boomfly
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

