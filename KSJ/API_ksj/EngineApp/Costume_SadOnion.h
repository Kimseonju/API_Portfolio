#pragma once
#include "Player_ItemCostume.h"

//아이템 코스튬 아이템먹을시 적용
//여러종류가있어서 Vector로 플레이어에 관리
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
    //스타트할때 아이템생성 이후 이름넣을떄 
    void SetAnimFrameTimer(float _Time) override;
};
