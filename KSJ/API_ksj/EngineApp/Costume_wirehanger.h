#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_wirehanger : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_wirehanger();
    ~Costume_wirehanger();

public: // delete constructer 
    Costume_wirehanger(const Costume_wirehanger& _Other) = delete;
    Costume_wirehanger(const Costume_wirehanger&& _Other) = delete;

public: // delete operator
    Costume_wirehanger& operator=(const Costume_wirehanger& _Other) = delete;
    Costume_wirehanger& operator=(const Costume_wirehanger&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 

};
