#pragma once
#include <EngineScene.h>

// ºÐ·ù : Scene
class EndScene : public EngineScene
{
private: // Static Var
public: // Static Func
private: // member Var
    bool m_MoviePlay;
public: // constructer destructer
    EndScene();
    ~EndScene();

public: // delete constructer 
    EndScene(const EndScene& _Other) = delete;
    EndScene(const EndScene&& _Other) = delete;

public: // delete operator
    EndScene& operator=(const EndScene& _Other) = delete;
    EndScene& operator=(const EndScene&& _Other) = delete;

public: // member Func
    void SceneUpdate() override;
    void Start() override;
};

