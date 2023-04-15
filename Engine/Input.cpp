#include "pch.h"
#include "Input.h"

Input::Input()
	: mCurrentKey(false),
	mPrevKey(false)
{
}

Input::~Input()
{
}

void Input::Initialize(HWND hWnd)
{
	mHwnd = hWnd;
}

void Input::Update()
{
	// 
	for (int i = 0; i < 255; i++)
	{
		mKeyStateArr[i].mPrevKey = mKeyStateArr[i].mCurrentKey;
		mKeyStateArr[i].mCurrentKey = HIWORD(GetAsyncKeyState(i));
	}

	POINT currentMousePos;

	// 현재 화면의 마우스 받기 
	GetCursorPos(&currentMousePos);
	ScreenToClient(mHwnd, &currentMousePos);

	// 마우스 현재 위치 받기
	mCurrentMousePos.mX = currentMousePos.x;
	mCurrentMousePos.mY = currentMousePos.y;
}

KEYSTATE Input::GetKeyState(int vk)
{
	// 네가지 상황 반환
	if (!mKeyStateArr[vk].mPrevKey && mKeyStateArr[vk].mCurrentKey)
		return KEYSTATE::DOWN;
	else if (!mKeyStateArr[vk].mPrevKey && !mKeyStateArr[vk].mCurrentKey)
		return KEYSTATE::NONE;
	else if (mKeyStateArr[vk].mPrevKey && !mKeyStateArr[vk].mCurrentKey)
		return KEYSTATE::UP;
	else
		return KEYSTATE::HOLD;
}