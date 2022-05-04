#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <functional>

// 분류 : 
// 용도 : 
// 설명 : 아이템 기본클래스 담당 (상속예정)
class EngineRendererBasic;
class Itemaltar;
class Item : public EngineActor
{
private:

    static LogicValue::ItemGroup ItemNumber;
public:
    static LogicValue::ItemGroup GetItemNumber()
    {
        return ItemNumber;
    }
    void NextItem()
    {
        ItemNumber = (LogicValue::ItemGroup)(static_cast<int>(ItemNumber)+  1);
        if (LogicValue::ItemGroup::MAX == ItemNumber)
        {
            ItemNumber = LogicValue::ItemGroup::haloofflies;
        }
    }
protected: // Static Var
    EngineRendererBasic* m_ItemRenderer;
    LogicValue::ItemGroup m_ItemNumber;
    Itemaltar* m_Itemaltar;
    float m_MoveCount;
    float m_MaxCount;
    int m_MaxMove;
    int m_Move;
    bool m_Up;
    float m_Speed;
public: // Static Func
private: // member Var
public: // constructer destructer
    Item();
    virtual ~Item();
public: // delete constructer 
    Item(const Item& _Other) = delete;
    Item(const Item&& _Other) = delete;

public: // delete operator
    Item& operator=(const Item& _Other) = delete;
    Item& operator=(const Item&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;

    void SetItemaltar(Itemaltar* _Itemaltar)
    {
        m_Itemaltar = _Itemaltar;
    }
    
    //void RenderItem();
    virtual void PlayerFarming() {}; //플레이어 아이템먹었을때 실행


    //아이템먹었을때 플레이어 위치만 상속시키기
    //하지만 지워질때는 item에 상속되있어서 알아서 지워짐
    virtual EngineRendererBasic* PlayerRenderItem() { return nullptr; };
};
