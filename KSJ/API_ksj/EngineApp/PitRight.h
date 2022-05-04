#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
class EngineRendererAnim;
class EngineRendererBasic;
//이동시 가속도필요
class PitRight : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    EngineRendererBasic* m_RenderBody;

public: // constructer destructer
    PitRight();
    ~PitRight();

public: // delete constructer 
    PitRight(const PitRight& _Other) = delete;
    PitRight(const PitRight&& _Other) = delete;

public: // delete operator
    PitRight& operator=(const PitRight& _Other) = delete;
    PitRight& operator=(const PitRight&& _Other) = delete;

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
