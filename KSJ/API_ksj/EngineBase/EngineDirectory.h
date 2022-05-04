#pragma once
#include "EnginePath.h"
class EngineFile;
class EngineDirectory : public EnginePath
{
private:
public: 
private:

public:
    static void GetCurrentDirectoryPath(EngineString& _String);
    static EngineString GetCurrentDirectoryPath();

public:
    EngineDirectory();
    ~EngineDirectory();

public:
    EngineDirectory(const EngineDirectory& _Other) = delete;
    EngineDirectory(const EngineDirectory&& _Other) = delete;

public: 
    EngineDirectory& operator=(const EngineString& _Other)
    {
    }

    EngineDirectory& operator=(const EngineDirectory& _Other) = delete;
    EngineDirectory& operator=(const EngineDirectory&& _Other) = delete;

public: 
    EngineString DirectoryName();

    void MoveChild(const EngineString& _Path);
    void MoveParent();
    void MoveParent(const EngineString& _DirName);
    std::vector<EngineFile> DirectoryAllFileToVector(const EngineString& _CheckPath = L"*.*");
};

