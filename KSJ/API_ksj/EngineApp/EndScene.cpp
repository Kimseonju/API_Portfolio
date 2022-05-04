#include "EndScene.h"
#include "TitleBackGround_ksj.h"
#include <EngineWindow.h>
#include <EngineInput.h>
#include "Core.h"
#include "Title_Title.h"
#include "Title_Start.h"
#include <EngineMovie.h>
#include <EngineDirectory.h>
#include "Core.h"
#include "TitleScene.h"
// Static Var
// Static Func

// member Var
EndScene::EndScene():
	m_MoviePlay(false)
{

}

EndScene::~EndScene()
{

}
// member Func

void EndScene::Start()
{
}
void EndScene::SceneUpdate()
{
	if (!m_MoviePlay)
	{
		EngineDirectory Dir;

		Dir.MoveParent(L"API_ksj");
		Dir.MoveChild(L"Res");
		Dir.MoveChild(L"Video");

		EngineString Path = Dir.GetPath() + L"Ending.avi";
		EngineMovie::Play(Path.c_str());
		EngineSound::Play(L"Ending.mp3", false, 0);
		EngineSound::Volume(L"Ending.mp3", 0.7f);
		m_MoviePlay = true;
	}

	if (m_MoviePlay &&!EngineMovie::IsPlay())
	{
		Core::SceneManager.CreateScene<TitleScene>(L"TitleScene1");
		Core::SceneManager.ChangeScene(L"TitleScene1");
	}
}