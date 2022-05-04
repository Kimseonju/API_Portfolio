#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �밢������ �����̴� ������Ʈ �ʿ� ������ ������ ����
//�̹��������ʿ�
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

