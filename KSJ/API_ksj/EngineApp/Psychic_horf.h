#pragma once
#include "Enemy.h"
//용도 :
//설명 : 유도탄 발사하는 몬스터
//이미지수정중
class EngineCollision;
class EngineRendererAnim;
class Psychic_horf : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	EngineRendererAnim* m_RenderEffect;
public: //constructer destructer
	Psychic_horf();
	~Psychic_horf();

public:
	Psychic_horf(const Psychic_horf& _Other) = delete;
	Psychic_horf(const Psychic_horf&& _Other) = delete;

public:
	Psychic_horf& operator=(const Psychic_horf& _Other) = delete;
	Psychic_horf& operator=(const Psychic_horf&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void FindStay() override;
	void AttackStart() override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

