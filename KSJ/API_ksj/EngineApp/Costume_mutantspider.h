#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_mutantspider : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_mutantspider();
    ~Costume_mutantspider();

public: // delete constructer 
    Costume_mutantspider(const Costume_mutantspider& _Other) = delete;
    Costume_mutantspider(const Costume_mutantspider&& _Other) = delete;

public: // delete operator
    Costume_mutantspider& operator=(const Costume_mutantspider& _Other) = delete;
    Costume_mutantspider& operator=(const Costume_mutantspider&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 

};
