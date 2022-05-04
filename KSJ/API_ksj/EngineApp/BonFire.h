#pragma once

#include <EngineActor.h>
#include <EngineRendererAnim.h>

class EngineRendererBasic;
class BonFire : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    EngineRendererAnim* RenderHead;
    EngineRendererAnim* RenderBody;
    float m_FireHP;
    float m_FireHPMax;
    bool m_Die;
public: // constructer destructer
    BonFire();
    ~BonFire();
public: // delete constructer 
    BonFire(const BonFire& _Other) = delete;
    BonFire(const BonFire&& _Other) = delete;

public: // delete operator
    BonFire& operator=(const BonFire& _Other) = delete;
    BonFire& operator=(const BonFire&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;
    void OffTask() override;
public:

    void StartCol(EngineCollision* _This, EngineCollision* _Other);
    void EndCol(EngineCollision* _This, EngineCollision* _Other);
    void StayCol(EngineCollision* _This, EngineCollision* _Other);
};
