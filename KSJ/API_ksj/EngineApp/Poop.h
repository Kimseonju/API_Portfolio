#pragma once
#include <EngineActor.h>

class EngineRendererBasic;
class Poop : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    int m_PoopHP;
    EngineRendererBasic* m_RenderBody;
    int m_ImageCount; //이미지 몇번째인지
    bool m_CheckSound;
public: // constructer destructer
    Poop();
    ~Poop();
public: // delete constructer 
    Poop(const Poop& _Other) = delete;
    Poop(const Poop&& _Other) = delete;

public: // delete operator
    Poop& operator=(const Poop& _Other) = delete;
    Poop& operator=(const Poop&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;
public:
    void StartCol(EngineCollision* _This, EngineCollision* _Other);
    void EndCol(EngineCollision* _This, EngineCollision* _Other);
    void StayCol(EngineCollision* _This, EngineCollision* _Other);
};
