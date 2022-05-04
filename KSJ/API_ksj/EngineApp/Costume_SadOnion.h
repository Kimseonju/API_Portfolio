#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_SadOnion : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var
   
public: // constructer destructer
    Costume_SadOnion();
    ~Costume_SadOnion();

public: // delete constructer 
    Costume_SadOnion(const Costume_SadOnion& _Other) = delete;
    Costume_SadOnion(const Costume_SadOnion&& _Other) = delete;

public: // delete operator
    Costume_SadOnion& operator=(const Costume_SadOnion& _Other) = delete;
    Costume_SadOnion& operator=(const Costume_SadOnion&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 
    void SetAnimFrameTimer(float _Time) override;
};
