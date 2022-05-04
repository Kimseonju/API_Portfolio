#pragma once
#include <EngineActor.h>
//용도 :
//설명 :Item_haloofflies
class EngineRendererAnim;
class ProtectionFly : public EngineActor
{
private: //static
public:  //static func
private: 
public: //member

	float m_Angle;
	EngineRendererAnim* m_RenderBody;
	EngineCollision* m_Collision;

public:
	void SetAngle(float _Angle)
	{
		m_Angle = _Angle;
	}

public: //constructer destructer
	ProtectionFly();
	~ProtectionFly();

	
public: 
	ProtectionFly(const ProtectionFly& _Other) = delete;
	ProtectionFly(const ProtectionFly&& _Other) = delete;

public:
	ProtectionFly& operator=(const ProtectionFly& _Other) = delete;
	ProtectionFly& operator=(const ProtectionFly&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
};

