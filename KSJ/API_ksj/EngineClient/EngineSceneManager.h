#pragma once

#include <map>
#include <EngineString.h>
#include "EngineScene.h"
// 분류 : 오브젝트 
// 용도 : 매니지먼트
// 설명 : 장면들을 만드는 것을 도와주고 그 장면들을 관리
//Scene들을 관리, 다음씬으로 넘어가기등
class EngineSceneManager
{
private: 
public: 
private: 
    std::map<EngineString, EngineScene*> m_AllScene;

    EngineScene* m_CurScene; //선택된 씬
    
    EngineScene* m_NextScene; //다음 씬

public:
    EngineScene* GetCurScene()
    {
        return m_CurScene;
    }

public:

    //씬을 만들고 넣어주는 템플릿
    template<typename SceneType>
    EngineScene* CreateScene(const EngineString& _Name)
    {
        std::map<EngineString, EngineScene*>::iterator FindIter
            = m_AllScene.find(_Name);

        if (m_AllScene.end() != FindIter)
        {
            return m_AllScene[_Name];
        }
        SceneType* NewScene = new SceneType();

        NewScene->Start();
        m_AllScene.insert(std::map<EngineString, EngineScene*>::value_type(_Name, NewScene));
        return NewScene;
    }


    //씬 찾아주는 기능
    EngineScene* FindScene(const EngineString& _Name);

    // 다음씬 선택하기
    void ChangeScene(const EngineString& _Name); 

    //다음씬 넘어가기
    void ChangeCheck(); 


public: 
    EngineSceneManager();
    ~EngineSceneManager();

public:
    EngineSceneManager(const EngineSceneManager& _Other) = delete;
    EngineSceneManager(const EngineSceneManager&& _Other) = delete;

public:
    EngineSceneManager& operator=(const EngineSceneManager& _Other) = delete;
    EngineSceneManager& operator=(const EngineSceneManager&& _Other) = delete;

public: 
};

