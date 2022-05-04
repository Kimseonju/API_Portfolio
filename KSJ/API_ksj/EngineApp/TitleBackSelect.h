#pragma once
#include <EngineActor.h>

class EngineRendererBasic;
class TitleBackSelect : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    bool m_Select;
    bool m_CamMove;
    float4 m_CamStartPos;
    float4 m_CamEndPos;
    float m_CamTime;
    EngineRendererBasic* m_RenderBody;
public: // constructer destructer
    TitleBackSelect();
    ~TitleBackSelect();

public: // delete constructer 
    TitleBackSelect(const TitleBackSelect& _Other) = delete;
    TitleBackSelect(const TitleBackSelect&& _Other) = delete;

public: // delete operator
    TitleBackSelect& operator=(const TitleBackSelect& _Other) = delete;
    TitleBackSelect& operator=(const TitleBackSelect&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;

    void MapMove();

    void MoveStart(bool _Select);
};


