#pragma once

enum class KEYSTATE
{
	NONE,
	HOLD,
	DOWN,
	UP
};

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 윈도우 창 내에서 키 입력을 위한 클래스. (키보드, 마우스)
/// </summary>
class Input
{
public:
	Input();
	Input(const Input& ref) {};
	Input& operator=(const Input& ref) {};
	~Input();

	static Input& GetInstance()
	{
		static Input instance;
		return instance;
	}

	void Initialize(HWND hWnd);

private:
	Vector2D mCurrentMousePos;		// 현재 마우스 위치

	HWND mHwnd;

	bool mCurrentKey;		// 현재 키상태
	bool mPrevKey;			// 이전 키상태

public:
	void Update();					// 키입력 초기화

	KEYSTATE GetKeyState(int vk);
	Vector2D GetCurrentMousePos() { return mCurrentMousePos; }
};

static Input mKeyStateArr[256];		// 키입력 받을 배열