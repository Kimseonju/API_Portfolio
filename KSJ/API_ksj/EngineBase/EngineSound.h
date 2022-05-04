#pragma once
#include "fmod.hpp"
#include "EngineDebug.h"
#include <map>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

//용도 :
//설명 :
class EngineString;
class EngineSound
{
public:
    class EngineSoundPlayer
    {
        friend EngineSound;
    private:
        FMOD::Channel* Channel;
    public:
        void Stop()
        {
            if (nullptr == Channel)
            {
                EngineDebug::AssertMsg("if (nullptr == Channel)");
            }

            Channel->stop();
        }

    public:
        EngineSoundPlayer() : Channel(nullptr)
        {

        }

    private:

        EngineSoundPlayer(FMOD::Channel* _Channel) : Channel(_Channel)
        {

        }
    };
private: //static
    static FMOD::System* m_pFmodSystem;
    static std::map<EngineString, EngineSound*> m_SoundMap;
    static std::map<EngineString, FMOD::Channel*> m_SoundChannel;

private:
    static void Init();

    class StaticInst
    {
        friend EngineSound;
    private:
        StaticInst();
        ~StaticInst();
    };
   
    friend StaticInst;
    static StaticInst Inst;

public: //member
    static void Update();
    static void Release();
    static void Load(const EngineString& _Path);
    static EngineSoundPlayer Play(const EngineString& _Name, bool _Bgm, int _LoopCount);
    static void Stop(const EngineString& _Name);
    static void Volume(const EngineString& _Name, float _volume);
private:  //static func
public:
private: //member
    FMOD::Sound* m_pSound;
public: //constructer destructer
	EngineSound();
	~EngineSound();

public: 
	EngineSound(const EngineSound& _Other) = delete;
	EngineSound(const EngineSound&& _Other) = delete;

public:
	EngineSound& operator=(const EngineSound& _Other) = delete;
	EngineSound& operator=(const EngineSound&& _Other) = delete;




private:

    void Create(const EngineString& _Path);
    FMOD::Channel* Play(const EngineString& _Name, bool check, bool _Bgm, int _LoopCount = 1);
    //boolcheck는 위 Play랑 분류용.. 
};

using SoundPlayer = EngineSound::EngineSoundPlayer;

