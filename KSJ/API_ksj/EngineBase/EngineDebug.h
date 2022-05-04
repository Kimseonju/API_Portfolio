#pragma once
#include "EngineString.h"

class EngineDebug
{
private:
public: 
    static void LeakCheck();
    static void AssertMsg(const EngineString& _ErrorMsg);
    static void OutPutMsg(const EngineString& _ErrorMsg);
    static void AssertMsg(const std::string& _ErrorMsg);

private: 

private:
    EngineDebug();
    ~EngineDebug();

public: 
    EngineDebug(const EngineDebug& _Other) = delete;
    EngineDebug(const EngineDebug&& _Other) = delete;

public:
    EngineDebug& operator=(const EngineDebug& _Other) = delete;
    EngineDebug& operator=(const EngineDebug&& _Other) = delete;

};

