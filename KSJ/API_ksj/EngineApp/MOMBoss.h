#pragma once
#include "Enemy.h"
#include <vector>
//�뵵 :
//���� : ���� ��Ʈ���ϴ� �ý���
class EngineCollision;
class EngineRendererAnim;
class EngineRendererBasic;
class MomLeg;
class MomBody;

class MOMBoss : public Enemy
{
private: //static
public:  //static func
private:
	//Leg�� ������ ������ ���� ������ �ƴ�
	MomLeg* m_MomLeg;
	std::vector<MomBody*> m_MomBody;

	float m_Timer;
	float m_EyeTimer;
	float m_LegTimer;
	int m_iEye;
	bool m_bPlayerAttack;
	float m_AttackSoundCount;

	float m_HitTimer;
	bool m_Hit;
public: //member
public: //constructer destructer
	MOMBoss();
	~MOMBoss();

public:
	MOMBoss(const MOMBoss& _Other) = delete;
	MOMBoss(const MOMBoss&& _Other) = delete;

public:
	MOMBoss& operator=(const MOMBoss& _Other) = delete;
	MOMBoss& operator=(const MOMBoss&& _Other) = delete;

	void Start() override;
	void Update() override;
	void OnTask() override;
	void PlayerAttack()
	{
		if (m_AttackSoundCount > 3.f)
		{
			m_bPlayerAttack = true;
			m_AttackSoundCount = 0.f;
		}
		
	}
public:
	void Hit()
	{
		m_Hit = true;
	}
	void UpdateNext() override;
public:
	//��� �����̸鼭 �ĸ���ȯ

	void Init();
public: //member
};

