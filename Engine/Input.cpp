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

	// ���� ȭ���� ���콺 �ޱ� 
	GetCursorPos(&currentMousePos);
	ScreenToClient(mHwnd, &currentMousePos);

	// ���콺 ���� ��ġ �ޱ�
	mCurrentMousePos.mX = currentMousePos.x;
	mCurrentMousePos.mY = currentMousePos.y;
}

KEYSTATE Input::GetKeyState(int vk)
{
	// �װ��� ��Ȳ ��ȯ
	if (!mKeyStateArr[vk].mPrevKey && mKeyStateArr[vk].mCurrentKey)
		return KEYSTATE::DOWN;
	else if (!mKeyStateArr[vk].mPrevKey && !mKeyStateArr[vk].mCurrentKey)
		return KEYSTATE::NONE;
	else if (mKeyStateArr[vk].mPrevKey && !mKeyStateArr[vk].mCurrentKey)
		return KEYSTATE::UP;
	else
		return KEYSTATE::HOLD;
}