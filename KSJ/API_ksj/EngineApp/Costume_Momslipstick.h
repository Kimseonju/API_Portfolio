#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_Momslipstick : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_Momslipstick();
    ~Costume_Momslipstick();

public: // delete constructer 
    Costume_Momslipstick(const Costume_Momslipstick& _Other) = delete;
    Costume_Momslipstick(const Costume_Momslipstick&& _Other) = delete;

public: // delete operator
    Costume_Momslipstick& operator=(const Costume_Momslipstick& _Other) = delete;
    Costume_Momslipstick& operator=(const Costume_Momslipstick&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 

};
