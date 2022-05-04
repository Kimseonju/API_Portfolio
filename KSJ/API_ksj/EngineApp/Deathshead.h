#pragma once
#include "Enemy.h"
//용도 :
//설명 : 대각선으로 움직이는 오브젝트 맵에 적들이 죽으면 죽음
//이미지수정필요
class EngineCollision;
class Deathshead : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float4 m_Dir;
public: //constructer destructer
	Deathshead();
	~Deathshead();

public:
	Deathshead(const Deathshead& _Other) = delete;
	Deathshead(const Deathshead&& _Other) = delete;

public:
	Deathshead& operator=(const Deathshead& _Other) = delete;
	Deathshead& operator=(const Deathshead&& _Other) = delete;

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

