//#pragma once
//
///// <summary>
///// Win32 관련 부분
///// </summary>
//class Window
//{
//public:
//	Window();
//	~Window();
//
//
//private:
//	HWND mHwnd;			// 만든 윈도우의 핸들
//
//public:
//	// 윈도 프로그래밍을 위한 초기화의 모든것
//	void Initialize();
//
//	// 윈도우 프로그래밍 안에서의 무한루프
//	void LoopAll();
//
//	bool MessageLoop(bool& isQuitMessage);
//
//
//	// 윈도우 프로그래밍이 끝날 때 해줘야 하는 것
//	void Finalize();
//
//	// 메세지를 받기 위한 콜백 함수
//	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//	HWND GetWindowHandle() const { return mHwnd; }
//};

// Comet : 없어도 무방한 클래스라고 판단됩니당 ..