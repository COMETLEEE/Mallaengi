#include "PreCompiledHeader.h"
#include "Game.h"
#define _CRTDBG_MAP_ALLOC

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR	lpCmdLine, int nCmdShow)
{
	TCHAR szAppName[] = _T("Mallaengi Project");
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	RegisterClass(&wndclass);

	RECT deskWnd;
	GetWindowRect(GetDesktopWindow(), &deskWnd);

	hWnd = CreateWindow(szAppName, szAppName, WS_POPUP,
		(deskWnd.right + deskWnd.left) / 2 - 960, 0, 1920, 1080, NULL, NULL, hInstance, NULL);

	// 혜성이용
	/*hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		100, 100, 1920, 1080, NULL, NULL, hInstance, NULL);*/

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			// Game Loop (Option이 켜지지 않았을 때 돌아가면 되는거지 ..?)
			if (Game::GetInstance().GameLoop())
				break;
		}
	}

	SoundManager::GetInstance()->DestroyInstance();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_CREATE:
		{
			// Game Initialize !
			Game::GetInstance().Initialize(hWnd);
		}
		break;

		case WM_SIZE:
		{
			// 창 사이즈가 변경되면 렌더타겟을 다시 설정해줍니다.
			UINT _width = LOWORD(lParam);
			UINT _height = HIWORD(lParam);
		}
		break;

		case WM_ACTIVATE:
		{
			// wParam으로 윈도우 창이 활성화 / 비활성화 되었다는 메시지가 들어온다.
			// 값에 따라 게임을 항상 위에 보여줄 것인지 옵션을 취소할 것인지 결정한다.
			if (wParam != false)
				SetWindowPos(hWnd, HWND_TOPMOST, 100, 0, 1920, 1080, SWP_NOSIZE | SWP_NOMOVE);
			else
				SetWindowPos(hWnd, HWND_NOTOPMOST, 100, 0, 1920, 1080, SWP_NOSIZE | SWP_NOMOVE);
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DISPLAYCHANGE:
		{

		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd,
				message, wParam, lParam);
	}

	return 0;
}