#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <functional>

// �з� : 
// �뵵 : 
// ���� : ������ �⺻Ŭ���� ��� (��ӿ���)
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
    virtual void PlayerFarming() {}; //�÷��̾� �����۸Ծ����� ����


    //�����۸Ծ����� �÷��̾� ��ġ�� ��ӽ�Ű��
    //������ ���������� item�� ��ӵ��־ �˾Ƽ� ������
    virtual EngineRendererBasic* PlayerRenderItem() { return nullptr; };
};
