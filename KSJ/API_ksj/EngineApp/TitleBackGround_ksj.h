#pragma once
#include <EngineActor.h>

// �з� : 
// �뵵 : 
// ���� : Ÿ��Ʋ ������ ����� �Ǿ��� ����

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


