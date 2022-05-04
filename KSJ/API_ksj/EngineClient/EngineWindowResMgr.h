#pragma once
#include <EngineWinImage.h>
#include <map>
#include <EngineString.h>

class EngineWindowResMgr
{
private:
public: 
    static EngineWindowResMgr& Inst(){
        static EngineWindowResMgr SingleInst;
        return SingleInst;
    }

    void Release();

private:
    std::map<EngineString, EngineWinImage*> m_Image;

public:
    EngineWinImage* FindImage(const EngineString& _Name);

    void ImageLoad(const EngineString& _Path);
    EngineWindowResMgr();
    ~EngineWindowResMgr();

public: 
    EngineWindowResMgr(const EngineWindowResMgr& _Other) = delete;
    EngineWindowResMgr(const EngineWindowResMgr&& _Other) = delete;

public: 
    EngineWindowResMgr& operator=(const EngineWindowResMgr& _Other) = delete;
    EngineWindowResMgr& operator=(const EngineWindowResMgr&& _Other) = delete;

public: 
};

