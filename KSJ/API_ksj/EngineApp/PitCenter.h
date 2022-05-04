#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
class EngineRendererAnim;
class EngineRendererBasic;
//이동시 가속도필요
class PitCenter : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    EngineRendererBasic* m_RenderBody;

public: // constructer destructer
    PitCenter();
    ~PitCenter();

public: // delete constructer 
    PitCenter(const PitCenter& _Other) = delete;
    PitCenter(const PitCenter&& _Other) = delete;

public: // delete operator
    PitCenter& operator=(const PitCenter& _Other) = delete;
    PitCenter& operator=(const PitCenter&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

public:
    void OffTask() override;
    void StartCol(EngineCollision* _This, EngineCollision* _Other);
    void EndCol(EngineCollision* _This, EngineCollision* _Other);
    void StayCol(EngineCollision* _This, EngineCollision* _Other);
};
