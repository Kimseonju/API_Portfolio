#pragma once
#include <EngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 타이틀 씬에서 배경이 되어줄 액터

class TitleBackGround_ksj : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    TitleBackGround_ksj();
    ~TitleBackGround_ksj();

public: // delete constructer 
    TitleBackGround_ksj(const TitleBackGround_ksj& _Other) = delete;
    TitleBackGround_ksj(const TitleBackGround_ksj&& _Other) = delete;

public: // delete operator
    TitleBackGround_ksj& operator=(const TitleBackGround_ksj& _Other) = delete;
    TitleBackGround_ksj& operator=(const TitleBackGround_ksj&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;
};


