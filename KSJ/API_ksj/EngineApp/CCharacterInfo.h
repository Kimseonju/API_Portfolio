#pragma once
#include "Player_ItemCostume.h"
#include <EngineRendererAnim.h>
#include "LogicValue.h"
class CCharacterInfo
{
private: // Static Var
public: // Static Func
private: // member Var
    //������ ����Ұ͵�
    //Shot Speed, Shot Range, m_Att ��
    float m_Speed;
    float m_AttackDelayMax;
    float m_AttackDelay;
    float m_ShotSpeed;
    float m_ShotRange;
    float m_Att;
    
    //HP 1���� ��Ʈ �ݰ� 2�� ��Ʈ�ϳ�
    int m_HP;
    int m_HPMax;

    //�÷��̾�
    int m_Bomb;
    int m_Coin;
    int m_Key;

    float4 m_DamageSpeed;
    float4    m_AccelSpeed;       // ���ӵ��ӵ�
    float4    m_Dir;       // ���������� ����
    float4    m_Accel;       // ���ӵ�   
    float4    m_SaveAccel;       // ��ü���� �浹���� �� ����
    float  m_ObjectMaxSpeed; //������Ʈ�� ���Ҷ� �� �ִ�ġ
    float   m_MaxSpeed;    // �ִ�ӷ� 
    float m_Timer;
public: // constructer destructer
    CCharacterInfo();
    ~CCharacterInfo();

    //���� ���ȼӵ�
    float4 GetUpdateSpeed()  const
    {
        return (GetAccelSpeed()+ m_DamageSpeed) * EngineTimer::MainTimer.GetFDeltaTime();
    }
    float4 GetDir() const
    {
        float4 Dir = (GetAccelSpeed() + m_DamageSpeed);
        Dir.Normalize();
        return Dir;
    }
    void AccelSpeedMove(float4 _Dir, float _Force)
    {
        m_AccelSpeed = _Dir * m_Speed * _Force;
    }
    void DamageAccel(float4 _Dir, float _Force)
    {
        m_DamageSpeed = _Dir * m_Speed * _Force;
    }
    void SetSpeed(float _Speed)
    {
        m_Speed = _Speed;
    }
    void SetAttackDelay(float _Delay)
    {
        m_AttackDelay = _Delay;
    }
    void SetAttackDelayMax(float _Delay)
    {
        m_AttackDelayMax = _Delay;
    }
    void SetShotSpeed(float _ShotSpeed)
    {
        m_ShotSpeed = _ShotSpeed;
    }
    void SetAtt(float _Att)
    {
        m_Att = _Att;
    } 
    void AddAtt(float _Att)
    {
        m_Att += _Att;
    }
    void SetHP(int _HP)
    {
        m_HP = _HP;
    }
    int GetHP() const
    {
        return m_HP;
    }
    void HPAdd(int _HP) 
    {
        m_HP += _HP;
        if (m_HP > m_HPMax)
        {
            m_HP = m_HPMax;
        }
    }
    void SetHPMax(int _HPMax)
    {
        m_HPMax = _HPMax;
    }
    int GetHPMax() const
    {
        return m_HPMax;
    }
    void StopX()
    {
        m_Dir.x = 0.f;
        m_AccelSpeed.x = 0.f;
        m_DamageSpeed.x = 0;
    }
    void StopY()
    {
        m_Dir.y = 0.f;
        m_AccelSpeed.y = 0.f;
        m_DamageSpeed.y = 0;
    }

    float4 GetAccelSpeed() const
    {
        return m_AccelSpeed;
    }
    void StopSpeed()
    {
        StopX();
        StopY();
    }
    float GetSpeed() const
    {
        return m_Speed;
    }
    float GetAttackDelay() const
    {
        return m_AttackDelay;
    }
    float GetAttackDelayMax() const
    {
        return m_AttackDelayMax;
    }
    float GetShotSpeed() const
    {
        return m_ShotSpeed;
    }
    float GetAtt() const
    {
        return m_Att;
    }


    void SetMaxSpeed(float _Speed) 
    {
        m_MaxSpeed = _Speed;
    }
    float GetMaxSpeed() const
    {
        return m_MaxSpeed;
    }
    float4& GetDir() 
    {
        return m_Dir;
    }
    void SetDir(const float4& _Dir)
    {
        m_Dir = _Dir;
    }


    void SetShotRange(float _Range)
    {
        m_ShotRange = _Range;
    }
    float GetShotRange() const
    {
        return m_ShotRange;
    }
public:
    //�÷��̾�
    ///////////////��ź////////////////
    void SetBomb(int _Bomb)
    {
        if (_Bomb > 99)
            _Bomb = 99;
        m_Bomb = _Bomb;
    }
    
    int GetBomb() const
    {
        return m_Bomb;
    }
    bool BombAdd(int _Bomb = 1)
    {
        m_Bomb += _Bomb;
        if (m_Bomb >= 99)
        {
            m_Bomb = 99;
            return false;
        }
        return true;
    }
    bool BombSub(int _Bomb = 1)
    {
        int temp = m_Bomb - _Bomb;
        if (temp < 0)
            return false;

        m_Bomb -= _Bomb;
        return true;
    }

    ///////////////����////////////////
    void SetCoin(int _Bomb)
    {
        m_Coin = _Bomb;
    }

    int GetCoin() const
    {
        return m_Coin;
    }

    bool CoinAdd(int _Coin = 1)
    {
        m_Coin += _Coin;
        if (m_Coin >= 99)
        {
            m_Coin = 99;
            return false;
        }
        m_Coin++;
        return true;
    }
    bool CoinSub(int _Coin = 1)
    {
        int temp = m_Coin - _Coin;
        if (temp < 0)
            return false;

        m_Coin -= _Coin;
        return true;
    }
    ///////////////Ű////////////////
    void SetKey(int _Key)
    {
        m_Key = _Key;
    }

    int GetKey() const
    {
        return m_Key;
    }

    bool KeyAdd(int _Key = 1)
    {
        m_Key += _Key;
        if (m_Key >= 99)
            m_Key = 99;
        m_Key++;
        return true;
    }
    bool KeySub(int _Key = 1)
    {
        int temp = m_Coin - _Key;
        if (temp < 0)
            return false;

        m_Key -= _Key;
        return true;
    }

public: // delete constructer 
    CCharacterInfo(const CCharacterInfo& _Other) = delete;
    CCharacterInfo(const CCharacterInfo&& _Other) = delete;
public: // delete operator
    CCharacterInfo& operator=(const CCharacterInfo& _Other) = delete;
    CCharacterInfo& operator=(const CCharacterInfo&& _Other) = delete;

public: // member Func
    
    void Update();
public: //�÷��̾� �� ����

};