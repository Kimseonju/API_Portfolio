#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_HolyGrail : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_HolyGrail();
    ~Costume_HolyGrail();

public: // delete constructer 
    Costume_HolyGrail(const Costume_HolyGrail& _Other) = delete;
    Costume_HolyGrail(const Costume_HolyGrail&& _Other) = delete;

public: // delete operator
    Costume_HolyGrail& operator=(const Costume_HolyGrail& _Other) = delete;
    Costume_HolyGrail& operator=(const Costume_HolyGrail&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 

};
