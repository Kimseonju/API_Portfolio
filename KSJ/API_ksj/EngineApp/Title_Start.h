#pragma once
#include <EngineActor.h>
#include <EngineRendererAnim.h>

// 분류 : 
// 용도 : 
// 설명 : 타이틀 씬에서 PressStart 애니메이션해줄 액터

class Title_Start : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineRendererAnim* RenderBody;

public: // constructer destructer
    Title_Start();
    ~Title_Start();

public: // delete constructer 
    Title_Start(const Title_Start& _Other) = delete;
    Title_Start(const Title_Start&& _Other) = delete;

public: // delete operator
    Title_Start& operator=(const Title_Start& _Other) = delete;
    Title_Start& operator=(const Title_Start&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
};
