#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �밢������ �����̴ٰ� ������ �����¿� �������� �߻�
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
	//������ Find ���°ų� 
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

