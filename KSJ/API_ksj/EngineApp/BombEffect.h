#pragma once
#include <EngineActor.h>

class EngineRendererAnim;
class EngineRendererBasic;

//용도 :
//설명 :
class BombEffect : public EngineActor
{
private: //static
	static int LayerNumber;
public:  //static func
	void NextLayer()
	{
		++LayerNumber;
		if (LayerNumber >= 8)
			LayerNumber = 0;
	}
private: 
public: //member

	//폭발
	EngineRendererAnim* m_RenderEffect;
	//검은재

	EngineRendererBasic* m_RenderLayer;


	EngineCollision* m_Collision;

	//콜리전 삭제 카운트 잠깐 나타났다가 사라진다.
	float m_time;
	float m_ColtimeMax;
	float m_livingtime;
	bool m_SecretCheck;
public: //constructer destructer
	BombEffect();
	~BombEffect();

public: 
	BombEffect(const BombEffect& _Other) = delete;
	BombEffect(const BombEffect&& _Other) = delete;

public:
	BombEffect& operator=(const BombEffect& _Other) = delete;
	BombEffect& operator=(const BombEffect&& _Other) = delete;

public: 
	// member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;
	void OffTask() override;
	void OpenSecret();
public:

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

