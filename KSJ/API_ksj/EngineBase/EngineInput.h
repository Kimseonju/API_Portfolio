#pragma once
#include <vector>
#include <map>
#include "EngineString.h"
#include "EngineDebug.h"
#include "EngineMath.h"

// 분류 : 
// 용도 : 업데이터(키 눌렀는지 확인), 매니저
// 설명 : 사용할 수 있는 키를 입력받고, 관리
class EngineInput
{
public:
    class EngineKey
    {
    public:
        std::vector<int> m_Key;

        bool Down;
        bool Press;
        bool Up;
        bool Free;

    public:
        template<typename ... REST>
        void PushKey(int _Key, REST ... _Arg)
        {
            if ('a' <= _Key && 'z' >= _Key)
            {
                _Key = toupper(_Key);
            }

            m_Key.push_back(_Key);
            PushKey(_Arg...);
        }

        void PushKey(int _Key)
        {
            if ('a' <= _Key && 'z' >= _Key)
            {
                _Key = toupper(_Key);
            }
            m_Key.push_back(_Key);
        }

    public:
        bool KeyCheck();
        void Update();
        void Reset();

    public:
        EngineKey();
        ~EngineKey();
    };

private:
public: 
private:
    static std::map<EngineString, EngineKey> m_KeyMap;

private:
    static EngineKey& FindKey(const EngineString& _Name);

public:

    template<typename ... REST>
    static void CreateKey(const EngineString& _Name, REST ... _ARG)
    {
        if (m_KeyMap.end() == m_KeyMap.find(_Name))
        {

            m_KeyMap.insert(std::map<EngineString, EngineKey>::value_type(_Name, EngineKey()));
        }
        else
        {
            EngineDebug::AssertMsg("if (m_KeyMap.end() != m_KeyMap.find(_Name))");
        }

        m_KeyMap[_Name].m_Key.reserve(sizeof...(_ARG));
        m_KeyMap[_Name].PushKey(_ARG...);
    }

public:
    static void Update();

    static bool IsFree(const EngineString& _Name);
    static bool IsUp(const EngineString& _Name);
    static bool IsPress(const EngineString& _Name);
    static bool IsDown(const EngineString& _Name);
    static void KeyReset();

public:
    static float4 MousePos();
public:
    EngineInput();
    ~EngineInput();

public:
    EngineInput(const EngineInput& _Other) = delete;
    EngineInput(const EngineInput&& _Other) = delete;

public:
    EngineInput& operator=(const EngineInput& _Other) = delete;
    EngineInput& operator=(const EngineInput&& _Other) = delete;

public: 
};

