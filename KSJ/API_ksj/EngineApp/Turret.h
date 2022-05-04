#pragma once
#include "Enemy.h"
//용도 :
//설명 : 플레이어 원거리 공격 터렛
class EngineCollision;
class Turret : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
public: //constructer destructer
	Turret();
	~Turret();

public:
	Turret(const Turret& _Other) = delete;
	Turret(const Turret&& _Other) = delete;

public:
	Turret& operator=(const Turret& _Other) = delete;
	Turret& operator=(const Turret&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void FindStay() override;
	void AttackStart()override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

