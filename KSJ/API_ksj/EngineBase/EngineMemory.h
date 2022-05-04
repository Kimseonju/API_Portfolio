#pragma once
#include <memory>

class EngineMemory
{
private: 
public: 
    template<typename Left, typename Right>
    static void Memcopy(Left& _Left, Right& _Test)
    {
        memcpy_s(&_Left, sizeof(Left), &_Test , sizeof(Right));
    }

    template<typename Data>
    static void MemZero(Data& _Value)
    {
        memset(&_Value, 0, sizeof(_Value));
    }

private: 

private: 
    EngineMemory();
    ~EngineMemory();

public: 
    EngineMemory(const EngineMemory& _Other) = delete;
    EngineMemory(const EngineMemory&& _Other) = delete;

public: 
    EngineMemory& operator=(const EngineMemory& _Other) = delete;
    EngineMemory& operator=(const EngineMemory&& _Other) = delete;

public:
};

