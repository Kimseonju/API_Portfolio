#pragma once
#include <EngineActor.h>

// �з� : 
// �뵵 : 
// ���� : Ÿ��Ʋ ������ ���������� ��¦ ȸ���ϸ鼭 ���ư��� ����
class EngineRendererBasic;
class Title_Title : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var

    EngineRendererBasic* RotRender;
    
    //true�� Right 
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
