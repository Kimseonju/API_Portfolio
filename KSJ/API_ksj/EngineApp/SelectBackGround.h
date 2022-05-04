#pragma once
#include <EngineActor.h>


class SelectBackGround : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    SelectBackGround();
    ~SelectBackGround();

public: // delete constructer 
    SelectBackGround(const SelectBackGround& _Other) = delete;
    SelectBackGround(const SelectBackGround&& _Other) = delete;

public: // delete operator
    SelectBackGround& operator=(const SelectBackGround& _Other) = delete;
    SelectBackGround& operator=(const SelectBackGround&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
};


