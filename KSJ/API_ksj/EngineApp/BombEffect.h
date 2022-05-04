#pragma once
#include <EngineActor.h>

class EngineRendererAnim;
class EngineRendererBasic;

//�뵵 :
//���� :
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

	//����
	EngineRendererAnim* m_RenderEffect;
	//������

	EngineRendererBasic* m_RenderLayer;


	EngineCollision* m_Collision;

	//�ݸ��� ���� ī��Ʈ ��� ��Ÿ���ٰ� �������.
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

