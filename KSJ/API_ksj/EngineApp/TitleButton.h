#pragma once
#include <EngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class TitleButton : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    float4 m_Scale;

public:
    float4 GetScale() {
        return m_Scale;
    }

    void SetScale(const float4& _Other)
    {
        m_Scale = _Other;
    }

public: // constructer destructer
    TitleButton();
    ~TitleButton();

public: // delete constructer 
    TitleButton(const TitleButton& _Other) = delete;
    TitleButton(const TitleButton&& _Other) = delete;

public: // delete operator
    TitleButton& operator=(const TitleButton& _Other) = delete;
    TitleButton& operator=(const TitleButton&& _Other) = delete;

public: // member Func
    void Update() override;
};

