#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾� �����Ϸ� �ٰ����� �ĸ�
class EngineCollision;
class Fly : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;

	//������ Ÿ��������� ȸ���ϴ¿뵵
	EngineActor* m_Target;
	float m_Angle;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	Fly();
	~Fly();

public: 
	Fly(const Fly& _Other) = delete;
	Fly(const Fly&& _Other) = delete;

public:
	Fly& operator=(const Fly& _Other) = delete;
	Fly& operator=(const Fly&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


	void BossTarget(EngineActor* _Target);
	void TargetOut();
public:
	//������ Find ���°ų� 
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;
public:


	//�浹
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

