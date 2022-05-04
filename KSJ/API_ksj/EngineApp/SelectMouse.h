#pragma once
#include <EngineActor.h>


class SelectMouse : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    SelectMouse();
    ~SelectMouse();

public: // delete constructer 
    SelectMouse(const SelectMouse& _Other) = delete;
    SelectMouse(const SelectMouse&& _Other) = delete;

public: // delete operator
    SelectMouse& operator=(const SelectMouse& _Other) = delete;
    SelectMouse& operator=(const SelectMouse&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
};


