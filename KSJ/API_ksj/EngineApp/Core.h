#pragma once
#include <EngineScene.h>
#include <EngineString.h>
#include <map>
#include <EngineSceneManager.h>

// 분류 : 컨텐츠 
// 용도 : 업데이터 or 매니저(Scene 관리)
// 설명 : 게임의 시작을 관리하고 게임의 전반적인 내용을 관리할 클래스
class Core
{
private: // Static Var
public: // Static Func

    static EngineSceneManager SceneManager;

private: // member Var

    std::map<EngineString, EngineScene*> m_AllScene;

private: // constructer destructer
    Core();
    ~Core();
public: // delete constructer 
    Core(const Core& _Other) = delete;
    Core(const Core&& _Other) = delete;

public: // delete operator
    Core& operator=(const Core& _Other) = delete;
    Core& operator=(const Core&& _Other) = delete;

public: // member Func
    static void Start();
    static void Update();

    static void KeyInput();
    static void ImageCut();
    static void End();
};

