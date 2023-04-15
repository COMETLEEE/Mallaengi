#include "pch.h"

//#include "Window.h"
//
//Window::Window()
//{
//}
//
//Window::~Window()
//{
//}
//
//void Window::Initialize()
//{
//	/// 윈도우 생성 
//	//
//	char	  szAppName[] = "Game Academy 2021";
//
//	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;		// 윈도 메시지를 받기 위한 콜백 함수
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = sizeof(LONG_PTR);
//	wcex.hInstance = NULL;
//	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wcex.lpszMenuName = NULL;
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.lpszClassName = szAppName;
//
//	/// 윈도 클래스 등록
//	RegisterClassEx(&wcex);
//
//	mHwnd = CreateWindow(
//		szAppName,
//		szAppName,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		800,
//		600,
//		NULL,
//		NULL,
//		NULL,
//		NULL
//	);
//
//	if (!mHwnd) return;
//}
//
//void Window::LoopAll()
//{
//	MSG msg;
//
//	while (true)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT)
//			{
//				break;
//			}
//
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			/// 윈도 메시지가 안들어올때도 게임은 처리를 해야 한다.
//			/// 1프레임당 나눠진 어떤 처리!!
//
//			/*
//			m_pRenderTarget->BeginDraw();
//
//			m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Red));
//
//			m_pRenderTarget->EndDraw();
//			*/
//		}
//	}
//}
//
//bool Window::MessageLoop(bool& isQuitMessage)
//{
//	isQuitMessage = false;
//
//	MSG msg;
//
//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//	{
//		if (msg.message == WM_QUIT)
//		{
//			isQuitMessage = true;
//		}
//
//		DispatchMessage(&msg);
//
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//void Window::Finalize()
//{
//	// 윈도 창을 종료할 때 처리 할 것이 있으면 여기에다가
//}
//
//LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//		case WM_SIZE:
//			break;
//		case WM_PAINT:
//			break;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			break;
//
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}