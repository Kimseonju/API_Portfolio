#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_spoonbender : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_spoonbender();
    ~Costume_spoonbender();

public: // delete constructer 
    Costume_spoonbender(const Costume_spoonbender& _Other) = delete;
    Costume_spoonbender(const Costume_spoonbender&& _Other) = delete;

public: // delete operator
    Costume_spoonbender& operator=(const Costume_spoonbender& _Other) = delete;
    Costume_spoonbender& operator=(const Costume_spoonbender&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 

};
