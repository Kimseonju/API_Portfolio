#pragma once
#include "Enemy.h"
//�뵵 :
//���� : ����ź �߻��ϴ� ����
//�̹���������
class EngineCollision;
class EngineRendererAnim;
class Psychicmaw : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	EngineRendererAnim* m_RenderEffect;
public: //constructer destructer
	Psychicmaw();
	~Psychicmaw();

public:
	Psychicmaw(const Psychicmaw& _Other) = delete;
	Psychicmaw(const Psychicmaw&& _Other) = delete;

public:
	Psychicmaw& operator=(const Psychicmaw& _Other) = delete;
	Psychicmaw& operator=(const Psychicmaw&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//������ Find ���°ų� 
	void FindStay() override;
	void AttackStart() override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

