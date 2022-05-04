#include "EngineSound.h"
#include "EngineDebug.h"
#include "EngineString.h"
#include "EnginePath.h"
#include <atlstr.h>
//static
//static func



FMOD::System* EngineSound::m_pFmodSystem = nullptr;
EngineSound::StaticInst EngineSound::Inst;
std::map<EngineString, EngineSound*> EngineSound::m_SoundMap;
std::map<EngineString, FMOD::Channel*> EngineSound::m_SoundChannel;

EngineSound::StaticInst::StaticInst()
{
    EngineSound::Init();
}

EngineSound::StaticInst::~StaticInst() {
}

void EngineSound::Release()
{

    {
        std::map<EngineString, EngineSound*>::iterator Start = m_SoundMap.begin();
        std::map<EngineString, EngineSound*>::iterator End = m_SoundMap.end();
        for (; Start != End; ++Start)
        {
            delete Start->second;
        }
        m_SoundMap.clear();
    }

    
    m_pFmodSystem->release();
}




EngineSound::EngineSound() : m_pSound(nullptr)
{
}

EngineSound::~EngineSound()
{
    if (nullptr != m_pSound)
    {
        m_pSound->release();
        m_pSound = nullptr;
    }
}

void EngineSound::Init()
{
    FMOD::System_Create(&m_pFmodSystem);
    if (nullptr == m_pFmodSystem)
    {
        EngineDebug::AssertMsg("if (nullptr == m_pFmodSystem)");
    }

    if (FMOD_OK != m_pFmodSystem->init(32, FMOD_DEFAULT, nullptr))
    {
        EngineDebug::AssertMsg("if (FMOD_OK != m_pFmodSystem->init(32, FMOD_DEFAULT, nullptr))");
    }
}

void EngineSound::Load(const EngineString& _Path)
{
    EngineSound* NewSound = new EngineSound();
    NewSound->Create(_Path);
    EngineString FileName = EnginePath::IOName(_Path);

    // 여기서 find해서

    // map 키가 제대로 들어갔다면
    std::pair<std::map<EngineString, EngineSound*>::iterator, bool> Result =
        m_SoundMap.insert(std::map<EngineString, EngineSound*>::value_type(FileName, NewSound));

    if (false == Result.second)
    {
        EngineDebug::AssertMsg("if (false == Result.second)");
    }

}

void EngineSound::Update()
{
    if (nullptr != m_pFmodSystem)
    {
        m_pFmodSystem->update();
    }
}



EngineSound::EngineSoundPlayer EngineSound::Play(const EngineString& _Name, bool _Bgm, int _LoopCount = 1)
{
    if (m_SoundMap.end() == m_SoundMap.find(_Name))
    {
        EngineDebug::AssertMsg("if (m_SoundMap.end() == m_SoundMap.find(_Name))");
    }
    return m_SoundMap[_Name]->Play(_Name, true, _Bgm,_LoopCount);
}

void EngineSound::Stop(const EngineString& _Name)
{
    if (m_SoundChannel.end() == m_SoundChannel.find(_Name))
    {
        return;
    }
    m_SoundChannel[_Name]->stop();
}

void EngineSound::Volume(const EngineString& _Name, float _volume)
{
    if (m_SoundChannel.end() == m_SoundChannel.find(_Name))
    {
        return;
    }
    m_SoundChannel[_Name]->setVolume(_volume);
}



void EngineSound::Create(const EngineString& _Path)
{
    std::string Path = _Path.GetConvertMultiByte(CP_UTF8);

    if (FMOD_OK != m_pFmodSystem->createSound(Path.c_str(), FMOD_DEFAULT, nullptr, &m_pSound))
    {
        EngineDebug::AssertMsg("if (FMOD_OK != m_pFmodSystem->createSound(Path.c_str(), FMOD_DEFAULT, nullptr, &m_pSound))");
    }
}

FMOD::Channel* EngineSound::Play(const EngineString& _Name, bool check, bool _Bgm, int _LoopCount )
{
    //촏
    FMOD::Channel* Ch = nullptr;

    if (_Bgm)
    {
        //사운드가없으면 만들어주기
        if (check)
        {
            if (m_SoundChannel.end() == m_SoundChannel.find(_Name))
            {
                if (FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, &Ch))
                {
                    EngineDebug::AssertMsg("FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, nullptr)");
                }
                Ch->setMode(FMOD_LOOP_NORMAL);
                if (FMOD_OK != Ch->setLoopCount(_LoopCount))
                {
                }

                std::pair<std::map<EngineString, FMOD::Channel*>::iterator, bool> Result =
                    m_SoundChannel.insert(std::map<EngineString, FMOD::Channel*>::value_type(_Name, Ch));
                return Ch;
            }
            else
            {
                bool soundcheck = false;
                m_SoundChannel[_Name]->isPlaying(&soundcheck);
                if (soundcheck)
                    return nullptr;
                else
                    m_pFmodSystem->playSound(m_pSound, nullptr, false, &m_SoundChannel[_Name]);
                return nullptr;
            }
        }
        
    }
    //효과음은 무한생성
    else
    {
        if (FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, &Ch))
        {
            EngineDebug::AssertMsg("FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, nullptr)");
        }
        Ch->setMode(FMOD_LOOP_NORMAL);
        if (FMOD_OK != Ch->setLoopCount(_LoopCount))
        {
        }

       // std::pair<std::map<EngineString, FMOD::Channel*>::iterator, bool> Result =
       //     m_SoundChannel.insert(std::map<EngineString, FMOD::Channel*>::value_type(_Name, Ch));
        return Ch;
    }


    


    return Ch;
}
