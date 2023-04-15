#include "pch.h"
#include "Engine.h"

#include "Input.h"
#include "Graphics.h"
#include "Timer.h"

Engine::Engine()
{
	
}

Engine::~Engine()
{
	// 엔진이 종료되면, 게임이 끝난 것
}

void Engine::Initialize(HWND hWnd)
{
	// Input 초기화
	GetInstance<Input>().Initialize(hWnd);

	// Graphics 초기화
	GetInstance<Graphics>().Initialize(hWnd);

	// Timer 초기화
	GetInstance<Timer>();
}