#include "EngineWindow.h"
#include <EngineDebug.h>
#include "EngineMovie.h"

#include <Windows.h>

float4 EngineWindow::m_Size;
float4 EngineWindow::m_Pos;
HWND EngineWindow::m_WindowHWnd = nullptr;
bool EngineWindow::m_bWindowProgress = true;
EngineWinImage EngineWindow::WindowMainImage;
EngineWinImage EngineWindow::DoubleBufferImage;
HDC EngineWindow::m_WindowDC;

EngineMovie* EngineWindow::MainMoviePlay = nullptr;
EngineWindow::EngineWindow()
{

}

EngineWindow::~EngineWindow()
{

}

void CALLBACK EngineWindow::OnGraphEvent(HWND hwnd, long evCode, LONG_PTR param1, LONG_PTR param2)
{
	switch (evCode)
	{
	case EC_COMPLETE:
	case EC_USERABORT:
	{
		wchar_t ArrName[256];
		GetWindowText(hwnd, ArrName, 256);
		MainMoviePlay->MovieStop();
		// g_pPlayer->Stop();
		break;
	}
	case EC_ERRORABORT:
		// NotifyError(hwnd, L"Playback error.");
	{
		wchar_t ArrName[256];
		GetWindowText(hwnd, ArrName, 256);
		MainMoviePlay->MovieStop();
		break;
	}
	}
}


__int64 EngineWindow::WINDOWEVENT(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue)
{

	//message=_EventType
	//wParam=_LValue
	//lParam=_SubValue
	// _hWnd 이벤트가 발생한 윈도우의 핸들

	switch (_EventType)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(m_WindowHWnd, &ps);

		if (MainMoviePlay->State() != STATE_NO_GRAPH && MainMoviePlay->HasVideo())
		{
			RECT rc;
			GetClientRect(m_WindowHWnd, &rc);

			MainMoviePlay->UpdateVideoWindow(&rc);

			// 이게 아마 동영상을 그려주는애이다.
			// The player has video, so ask the player to repaint. 
			MainMoviePlay->Repaint(hdc);
		}
		else
		{
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		}
		EndPaint(m_WindowHWnd, &ps);

	}
	break;
	case WM_SIZE:
	{
		RECT rc;
		GetClientRect(m_WindowHWnd, &rc);

		MainMoviePlay->UpdateVideoWindow(&rc);
		return 0;
	}

	case WM_DISPLAYCHANGE:
	{
		MainMoviePlay->DisplayModeChanged();
		break;
	}
	case WM_GRAPH_EVENT:
	{
		MainMoviePlay->HandleGraphEvent(OnGraphEvent);
		// g_pPlayer->HandleGraphEvent(OnGraphEvent);
		return 0;
	}


	case WM_DESTROY:
	{
		delete MainMoviePlay;
		m_bWindowProgress = false;
		break;
	}
	default:
		return DefWindowProcW(_hWnd, _EventType, _LValue, _SubValue);
	}
	
	
	return 0;
}

void EngineWindow::BackBufferCopy()
{
	WindowMainImage.BitBlt(DoubleBufferImage);
}

void EngineWindow::CreateGameEngineWindow(HINSTANCE _ProcessHandle, const EngineString& _Name, float4 _Pos, float4 _Size)
{

	{
		WNDCLASSEXW WCEX;

		WCEX.cbSize = sizeof(WNDCLASSEXW);
		WCEX.style = CS_HREDRAW | CS_VREDRAW;

		WCEX.lpfnWndProc = &EngineWindow::WINDOWEVENT;

		WCEX.cbClsExtra = 0;
		WCEX.cbWndExtra = 0;

		WCEX.hInstance = _ProcessHandle;

		WCEX.hIcon = nullptr;
		WCEX.hIconSm = nullptr;

		WCEX.hCursor = nullptr;

		WCEX.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

		WCEX.lpszMenuName = nullptr;


		WCEX.lpszClassName = L"DEFWINDOW";

		if (0 == RegisterClassExW(&WCEX))
		{
			unsigned int ErrorCode = GetLastError();

			EngineDebug::AssertMsg(L"if (0 == RegisterClassExW(&WCEX))");
		}

	}
	{

		RECT rt = { 0,0,_Size.ix(),_Size.iy() };
		
		m_WindowHWnd = CreateWindowW(L"DEFWINDOW", _Name.c_str(), WS_OVERLAPPEDWINDOW, _Pos.ix(), _Pos.iy(), rt.right, rt.bottom, nullptr, nullptr, _ProcessHandle, 0);

		
		if (nullptr == m_WindowHWnd)
		{
			EngineDebug::AssertMsg(L"if (nullptr == m_WindowHWnd)");
			return;
		}

		MainMoviePlay = new EngineMovie(m_WindowHWnd);

		ShowWindow(m_WindowHWnd, SW_SHOW);
		SetSizeAndPos(_Pos, _Size);
		UpdateWindow(m_WindowHWnd);

		m_WindowDC = GetDC(m_WindowHWnd);

		WindowMainImage.Create(m_WindowDC);
		DoubleBufferImage.Create(_Size);


	}

}

float4 EngineWindow::GetSize()
{
	return m_Size;
}

void EngineWindow::SetSize(float4 _Size)
{
	SetSizeAndPos(m_Pos, _Size);
}

void EngineWindow::SetPos(float4 _Pos) 
{
	SetSizeAndPos(_Pos, m_Size);
}

void EngineWindow::SetSizeAndPos(float4 _Pos, float4 _Size)
{
	m_Size = _Size;
	m_Pos = _Pos;
	RECT rc = { 0,0,_Size.ix(), _Size.iy() };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_WindowHWnd, HWND_BOTTOM, _Pos.ix(), _Pos.iy(), rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

}