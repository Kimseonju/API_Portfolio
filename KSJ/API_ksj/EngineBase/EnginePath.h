#pragma once
#include "EngineString.h"
class EnginePath : public EngineString
{
public:
    static bool IsExist(const EngineString& _Path);
    static EngineString IOName(const EngineString& _Path)
    {
        EngineString ReturnName = _Path.CutIndex(_Path.find_last_index(L"\\", _Path.size() - 2), _Path.size());
        ReturnName.EraseAll(L"\\");
        return ReturnName;

    }

public:
    bool IsFile()
    {
    }

    EngineString IOName()
    {
        return IOName(*this);
    }

public:
    EngineString GetPath()
    {
        return *this;
    }

public: 
    bool IsExist();

public: 
    EnginePath();
    EnginePath(const EngineString& _Path);
    ~EnginePath();
};

