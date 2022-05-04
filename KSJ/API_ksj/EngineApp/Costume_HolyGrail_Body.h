#pragma once
#include "Player_ItemCostume.h"

//������ �ڽ�Ƭ �����۸����� ����
//�����������־ Vector�� �÷��̾ ����
class EngineRendererAnim;
class Costume_HolyGrail_Body : public Player_ItemCostume
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Costume_HolyGrail_Body();
    ~Costume_HolyGrail_Body();

public: // delete constructer 
    Costume_HolyGrail_Body(const Costume_HolyGrail_Body& _Other) = delete;
    Costume_HolyGrail_Body(const Costume_HolyGrail_Body&& _Other) = delete;

public: // delete operator
    Costume_HolyGrail_Body& operator=(const Costume_HolyGrail_Body& _Other) = delete;
    Costume_HolyGrail_Body& operator=(const Costume_HolyGrail_Body&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
public:
    //��ŸƮ�Ҷ� �����ۻ��� ���� �̸������� 
    void SetAnimFrameTimer(float _Time) override;
};
