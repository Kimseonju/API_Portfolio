#pragma once
#include "Enemy.h"
//용도 :
//설명 : 대각선으로 움직이다가 죽으면 상하좌우 빨간눈물 발사
class EngineCollision;
class Redboomfly : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float4 m_Dir;
public: //constructer destructer
	Redboomfly();
	~Redboomfly();

public:
	Redboomfly(const Redboomfly& _Other) = delete;
	Redboomfly(const Redboomfly&& _Other) = delete;

public:
	Redboomfly& operator=(const Redboomfly& _Other) = delete;
	Redboomfly& operator=(const Redboomfly&& _Other) = delete;

public: // member Func
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

