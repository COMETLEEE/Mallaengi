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

	// �����̿�
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
			// Game Loop (Option�� ������ �ʾ��� �� ���ư��� �Ǵ°��� ..?)
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
			// â ����� ����Ǹ� ����Ÿ���� �ٽ� �������ݴϴ�.
			UINT _width = LOWORD(lParam);
			UINT _height = HIWORD(lParam);
		}
		break;

		case WM_ACTIVATE:
		{
			// wParam���� ������ â�� Ȱ��ȭ / ��Ȱ��ȭ �Ǿ��ٴ� �޽����� ���´�.
			// ���� ���� ������ �׻� ���� ������ ������ �ɼ��� ����� ������ �����Ѵ�.
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