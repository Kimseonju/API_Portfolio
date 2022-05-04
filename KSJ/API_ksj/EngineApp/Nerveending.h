#pragma once
#include "Enemy.h"
//�뵵 :
//���� : ���ڸ����� ���Ÿ��� ��
//�ʿ�����Ʈó�� ����ؾ���
class EngineCollision;
class Nerveending : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
public: //constructer destructer
	Nerveending();
	~Nerveending();

public:
	Nerveending(const Nerveending& _Other) = delete;
	Nerveending(const Nerveending&& _Other) = delete;

public:
	Nerveending& operator=(const Nerveending& _Other) = delete;
	Nerveending& operator=(const Nerveending&& _Other) = delete;

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

