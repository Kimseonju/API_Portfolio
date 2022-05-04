#pragma once
#include "Enemy.h"
//용도 :
//설명 : 매우큰똥 피도 갈색피 미니똥소환함
class EngineCollision;
class Dinga : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_MoveTime;
	float4 m_Rad;

public: //constructer destructer
	Dinga();
	~Dinga();

public:
	Dinga(const Dinga& _Other) = delete;
	Dinga(const Dinga&& _Other) = delete;

public:
	Dinga& operator=(const Dinga& _Other) = delete;
	Dinga& operator=(const Dinga&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;
	void AttackStart()override;
	void AttackStay() override;

public:
	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

