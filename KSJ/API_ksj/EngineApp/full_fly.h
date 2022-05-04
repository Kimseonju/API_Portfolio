#pragma once
#include "Enemy.h"
//�뵵 :
//���� : ���� �Ѿư�
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
	//������ Find ���°ų� 
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

