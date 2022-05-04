#pragma once
#include "Enemy.h"
//용도 :
//설명 : 미니똥 갈색피
class EngineCollision;
class Dip : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	Dip();
	~Dip();

public:
	Dip(const Dip& _Other) = delete;
	Dip(const Dip&& _Other) = delete;

public:
	Dip& operator=(const Dip& _Other) = delete;
	Dip& operator=(const Dip&& _Other) = delete;

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

public:
	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

