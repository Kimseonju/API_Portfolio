#pragma once
#include <EngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 타이틀 씬에서 오른쪽으로 살짝 회전하면서 돌아가는 액터
class EngineRendererBasic;
class Title_Title : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var

    EngineRendererBasic* RotRender;
    
    //true는 Right 
    bool m_LeftRight;
    bool onePlay;
    float m_Angle;
public: // constructer destructer
    Title_Title();
    ~Title_Title();

public: // delete constructer 
    Title_Title(const Title_Title& _Other) = delete;
    Title_Title(const Title_Title&& _Other) = delete;

public: // delete operator
    Title_Title& operator=(const Title_Title& _Other) = delete;
    Title_Title& operator=(const Title_Title&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
};
