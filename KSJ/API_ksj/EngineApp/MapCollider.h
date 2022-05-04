#pragma once
#include <EngineActor.h>
class EngineRendererBasic;
class MapCollider : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
public: // constructer destructer

    MapCollider();
    ~MapCollider();

public: // delete constructer 
    MapCollider(const MapCollider& _Other) = delete;
    MapCollider(const MapCollider&& _Other) = delete;

public: // delete operator
    MapCollider& operator=(const MapCollider& _Other) = delete;
    MapCollider& operator=(const MapCollider&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;
};

