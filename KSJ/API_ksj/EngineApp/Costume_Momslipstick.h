#pragma once
#include "Player_ItemCostume.h"

//아이템 코스튬 아이템먹을시 적용
//여러종류가있어서 Vector로 플레이어에 관리
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
    //스타트할때 아이템생성 이후 이름넣을떄 

};
