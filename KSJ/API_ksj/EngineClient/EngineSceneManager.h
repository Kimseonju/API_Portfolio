#pragma once

#include <map>
#include <EngineString.h>
#include "EngineScene.h"
// �з� : ������Ʈ 
// �뵵 : �Ŵ�����Ʈ
// ���� : ������ ����� ���� �����ְ� �� ������ ����
//Scene���� ����, ���������� �Ѿ���
class EngineSceneManager
{
private: 
public: 
private: 
    std::map<EngineString, EngineScene*> m_AllScene;

    EngineScene* m_CurScene; //���õ� ��
    
    EngineScene* m_NextScene; //���� ��

public:
    EngineScene* GetCurScene()
    {
        return m_CurScene;
    }

public:

    //���� ����� �־��ִ� ���ø�
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


    //�� ã���ִ� ���
    EngineScene* FindScene(const EngineString& _Name);

    // ������ �����ϱ�
    void ChangeScene(const EngineString& _Name); 

    //������ �Ѿ��
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

