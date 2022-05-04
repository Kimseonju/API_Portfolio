#pragma once
#include "Enemy.h"
//용도 :
//설명 : 플레이어위치에있다가 일정시간이지나면 멈추고 찍어누르는 오브젝트
class EngineCollision;
class EngineRendererBasic;
class Moms_hand : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_Time;
	EngineRendererBasic* m_Shadow;

public: //constructer destructer
	Moms_hand();
	~Moms_hand();

public:
	Moms_hand(const Moms_hand& _Other) = delete;
	Moms_hand(const Moms_hand&& _Other) = delete;

public:
	Moms_hand& operator=(const Moms_hand& _Other) = delete;
	Moms_hand& operator=(const Moms_hand&& _Other) = delete;

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
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;
	void AttackStart() override;
	void AttackStay() override;

	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

