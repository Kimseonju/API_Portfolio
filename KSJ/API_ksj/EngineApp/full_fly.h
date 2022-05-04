#pragma once
#include "Enemy.h"
//용도 :
//설명 : 적을 쫓아감
class EngineCollision;
class full_fly : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	full_fly();
	~full_fly();

public:
	full_fly(const full_fly& _Other) = delete;
	full_fly(const full_fly&& _Other) = delete;

public:
	full_fly& operator=(const full_fly& _Other) = delete;
	full_fly& operator=(const full_fly&& _Other) = delete;

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

	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

