#pragma once
#include <EngineActor.h>

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Player_ItemCostume : public EngineActor
{
private: // Static Var
public: // Static Func
protected: // member Var
    EngineRendererAnim* m_RenderHead;

public:
    EngineRendererAnim* GetRenderHead()
    {
        return m_RenderHead;
    }
public: // constructer destructer
    Player_ItemCostume();
    ~Player_ItemCostume();

    void ChangeAnimationdir(const EngineString& _dir);
    void FirstAnimationdir(const EngineString& _dir);
    void FirstAnimationclear();
public: // delete constructer 
    Player_ItemCostume(const Player_ItemCostume& _Other) = delete;
    Player_ItemCostume(const Player_ItemCostume&& _Other) = delete;

public: // delete operator
    Player_ItemCostume& operator=(const Player_ItemCostume& _Other) = delete;
    Player_ItemCostume& operator=(const Player_ItemCostume&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    virtual void SetAnimFrameTimer(float _Time);
    virtual void SetCharacterFly();
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 
    
};
