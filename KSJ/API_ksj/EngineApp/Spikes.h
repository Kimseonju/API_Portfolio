#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
class EngineRendererAnim;
class EngineRendererBasic;
//이동시 가속도필요
class Spikes : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    float m_Count;
    float m_CountMax;
    bool m_State; //0은 공격 1은 공격끝
    EngineRendererAnim* m_RenderBody;

public: // constructer destructer
    Spikes();
    ~Spikes();


public: // delete constructer 
    Spikes(const Spikes& _Other) = delete;
    Spikes(const Spikes&& _Other) = delete;

public: // delete operator
    Spikes& operator=(const Spikes& _Other) = delete;
    Spikes& operator=(const Spikes&& _Other) = delete;

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
