#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_catoninetails : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_catoninetails();
    ~Costume_catoninetails();

public: // delete constructer 
    Costume_catoninetails(const Costume_catoninetails& _Other) = delete;
    Costume_catoninetails(const Costume_catoninetails&& _Other) = delete;

public: // delete operator
    Costume_catoninetails& operator=(const Costume_catoninetails& _Other) = delete;
    Costume_catoninetails& operator=(const Costume_catoninetails&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 

};
