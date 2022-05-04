#pragma once
#include "Enemy.h"
//용도 :
//설명 : 급가속으로 플레이어에게 다가가는 똥덩어리 (중간크기) 갈색피
class EngineCollision;
class Squirt : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float4 m_Dir;
public: //constructer destructer
	Squirt();
	~Squirt();

public:
	Squirt(const Squirt& _Other) = delete;
	Squirt(const Squirt&& _Other) = delete;

public:
	Squirt& operator=(const Squirt& _Other) = delete;
	Squirt& operator=(const Squirt&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void FindStart() override;
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void AttackStart()override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

public:
	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

