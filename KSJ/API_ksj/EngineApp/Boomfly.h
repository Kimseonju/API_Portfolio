#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �밢������ �����̴ٰ� ������ ����
class EngineCollision;
class Boomfly : public Enemy
{
private: // Static Var
public: // Static Boomfly
private: // member Var

	EngineCollision* m_Collision;
	float4 m_Dir;
public: //constructer destructer
	Boomfly();
	~Boomfly();

public:
	Boomfly(const Boomfly& _Other) = delete;
	Boomfly(const Boomfly&& _Other) = delete;

public:
	Boomfly& operator=(const Boomfly& _Other) = delete;
	Boomfly& operator=(const Boomfly&& _Other) = delete;

public: // member Boomfly
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

