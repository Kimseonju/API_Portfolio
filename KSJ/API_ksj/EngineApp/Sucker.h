#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾� �����Ϸ� �ٰ����� �ĸ� ������ �����¿촫���߻�
class EngineCollision;
class Sucker : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	Sucker();
	~Sucker();

public:
	Sucker(const Sucker& _Other) = delete;
	Sucker(const Sucker&& _Other) = delete;

public:
	Sucker& operator=(const Sucker& _Other) = delete;
	Sucker& operator=(const Sucker&& _Other) = delete;

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

