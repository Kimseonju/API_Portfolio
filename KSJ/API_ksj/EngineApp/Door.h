#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
class EngineRendererBasic;
class EngineRendererAnim;

class Door : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    bool m_Open;
    EngineRendererBasic* m_MainDoor;
    EngineRendererBasic* m_BossDoorLayer;
    EngineRendererBasic* m_Space;
    EngineRendererAnim* m_LeftDoor;
    EngineRendererAnim* m_RightDoor;
    LogicValue::RoomType m_Type;
    float4 m_Dir;
    float m_Timer;
    //ÆøÅº¸Â¾Æ¼­ ¿­·È´ÂÁö ¾È¿­·È´ÂÁö °Ë»çÇÏ´Â°Í
    bool m_SecretCheck;
public:

    void SetOpen(bool _Open)
    {
        if (m_Open != _Open)
            m_Timer = 0.f;
        m_Open = _Open;
    }
    void SetSecretOpen()
    {
        m_SecretCheck = true;
    }

    bool SecretCheck()
    {
        return m_SecretCheck;
    }
    LogicValue::RoomType GetRoomType()
    {
        return m_Type;
    }
    void SetDoorImage(int _room, const float4& pos);
public: // constructer destructer
    Door();
    ~Door();

public: // delete constructer 
    Door(const Door& _Other) = delete;
    Door(const Door&& _Other) = delete;

public: // delete operator
    Door& operator=(const Door& _Other) = delete;
    Door& operator=(const Door&& _Other) = delete;


public: // member Func
    void Start() override;
    void Update() override;

    void BossOpen();
    void BossClose();
};
