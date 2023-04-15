#pragma once
#include "Graphics.h"
#include "Input.h"
#include "Timer.h"

 /// <summary>
 /// 
 /// 모든 엔진의 기능을 사용할 수 있게 하는 클래스
 /// 그런데, 이미 모든 엔진 코어의 구성 요소가 싱글톤으로 되어있는데 .. 이게 의미가 있나 싶음.
 /// </summary>
class Engine
{
public:

	// Singlton 
	Engine();
	Engine(const Engine& ref) {};
	Engine& operator=(const Engine& ref) {};
	~Engine();

	static Engine& GetInstance()
	{
		static Engine instance;
		return instance;
	}

public:
	void Initialize(HWND hWnd);

	// 이걸로 엔진 기능을 뽑아서 쓸꺼야
	template <typename T>
	T& GetInstance()
	{
		return T::GetInstance();
	}
};