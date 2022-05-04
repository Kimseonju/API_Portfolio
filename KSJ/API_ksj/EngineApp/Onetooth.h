#pragma once
#include "Enemy.h"
//용도 :
//설명 : 플레이어 공격하러 쫓아가는 매우 큰 박쥐
//이미지수정중
class EngineCollision;
class Onetooth : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	Onetooth();
	~Onetooth();

public:
	Onetooth(const Onetooth& _Other) = delete;
	Onetooth(const Onetooth&& _Other) = delete;

public:
	Onetooth& operator=(const Onetooth& _Other) = delete;
	Onetooth& operator=(const Onetooth&& _Other) = delete;

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

