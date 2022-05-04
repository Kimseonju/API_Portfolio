#pragma once
#include <EngineBasePublic.h>
#include <Windows.h>
#include <EngineString.h>
#include "EngineWinImage.h"
#include <EngineTimer.h>
#include <EngineInput.h>
#include <EngineSound.h>
// 傈何static 规侥栏肺 贸府
class EngineMovie;
class EngineWindow
{
private:

    static float4 m_Size;
    static float4 m_Pos;
    static bool m_bWindowProgress;

    static HWND m_WindowHWnd;

	static HDC m_WindowDC;
	static EngineWinImage WindowMainImage;
	static EngineWinImage DoubleBufferImage;
	static EngineMovie* MainMoviePlay;


	static void OnGraphEvent(HWND hwnd, long evCode, LONG_PTR param1, LONG_PTR param2);
    static __int64 WINDOWEVENT(HWND, unsigned int, unsigned __int64, __int64);


public:
	static HWND GetHWnd()
	{
		return m_WindowHWnd;
	}

	static HDC GetWindowDC()
	{
		return WindowMainImage.ImageDC();
	}

	static HDC GetBackBufferDC()
	{
		return DoubleBufferImage.ImageDC();
	}
	static EngineWinImage& GetWindowImage()
	{
		return WindowMainImage;
	}

	static EngineWinImage& GetBackBufferImage()
	{
		return DoubleBufferImage;
	}

public:
	static void BackBufferCopy();

	static void WindowEnd()
	{
		m_bWindowProgress = false;
	}

public: 
	template<typename Updater>
	static void Loop()
	{
		Updater::Start();
		MSG MsgData;

		while (m_bWindowProgress)
		{
			EngineTimer::MainTimer.CalTime();
			EngineInput::Update();
			EngineSound::Update();

			if (0 != PeekMessage(&MsgData, m_WindowHWnd, 0, 0, PM_REMOVE))
			{
				
				DispatchMessage(&MsgData);
				Updater::Update();
			}
			else
			{
				Updater::Update();
			}
		}

		Updater::End();

		if (true)
		{
			DestroyWindow(m_WindowHWnd);
			m_WindowHWnd = nullptr;
		}

	}
	static void CreateGameEngineWindow(HINSTANCE _ProcessHandle, const EngineString& _Name, float4 _Pos, float4 _Size);
private:

public: 
    EngineWindow();
    ~EngineWindow();

public:
    EngineWindow(const EngineWindow& _Other) = delete;
    EngineWindow(const EngineWindow&& _Other) = delete;

public: 
    EngineWindow& operator=(const EngineWindow& _Other) = delete;
    EngineWindow& operator=(const EngineWindow&& _Other) = delete;

public:

	static float4 GetSize();

    static void SetSize(float4 _Size);
    static void SetPos(float4 _Pos);
    static void SetSizeAndPos(float4 _Pos, float4 _Size);

	static float4 MousePos()
	{
		POINT P;
		GetCursorPos(&P);
		ScreenToClient(m_WindowHWnd, &P);

		return { (float)P.x, (float)P.y };

	}
};

