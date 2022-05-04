#pragma once
#include <EngineScene.h>

// 분류 : Scene
// 용도 : 메인화면 (대기화면)
// 설명 : 게임로고 뜨게하는 클래스
class TitleBackSelect;
class TitleScene : public EngineScene
{
private: // Static Var
public: // Static Func
private: // member Var
    bool m_Select;
    bool GameStart;
    EngineActor* m_SelectMouse;
    TitleBackSelect* m_SelectBack;
    bool m_Title;
    float m_CamTime;
    bool m_CamMove;
    float4 m_CamStartPos;
    float4 m_CamEndPos;
public: // constructer destructer
    TitleScene();
    ~TitleScene();

public: // delete constructer 
    TitleScene(const TitleScene& _Other) = delete;
    TitleScene(const TitleScene&& _Other) = delete;

public: // delete operator
    TitleScene& operator=(const TitleScene& _Other) = delete;
    TitleScene& operator=(const TitleScene&& _Other) = delete;

public: // member Func
    void SceneUpdate() override;
    void Start() override;
    void MapMove();
};

