#include "pch.h"
#include "Timer.h"

Timer::Timer()
	: mSecondsPerCount(0.0), mDeltaCount(0), mPreviousCount(0), mCurrentCount(0)
	,mDeltaTime(0)
{
	// 카운터 체크. 1초당 몇 번을 세는 것인가?
	QueryPerformanceFrequency((LARGE_INTEGER*)&mCountsPerSec);

	QueryPerformanceCounter((LARGE_INTEGER*)&mPreviousCount);

	// 1카운트당 몇 초나 걸리나?
	mSecondsPerCount = 1.0 / (double)mCountsPerSec;
}

Timer::~Timer()
{
}

float Timer::GetEngineTime()
{
	// 처음 시작 고정 저장
	static ULONGLONG oldTime = GetTickCount64();

	// 현재의 시간
	ULONGLONG nowTime = GetTickCount64();

	float dTime = (nowTime - oldTime) * 0.001f;		// 겟틱카운트가 1000이므로 곱해주기

	oldTime = nowTime;

	return dTime;
}

float Timer::GetDeltaTime()
{
	mDeltaTime = mDeltaCount * mSecondsPerCount;

	// 값이 double에서 float로 잘리지만 그것이 중요한 함수는 아니다.
	// 밀리세컨드로 변환 해 준다.
	return (float)mDeltaTime * 1000.0f;
}

float Timer::GetFPS()
{
	if (mDeltaTime != 0)
	{
		return (float)(1.0 / mDeltaTime);
	}
	return 0;
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrentCount);

	// Time difference between this frame and the previous.
	mDeltaCount = (mCurrentCount - mPreviousCount);

	// 카운트와 시간을 분리한다.
	mDeltaTime = mDeltaCount * mSecondsPerCount;

	// Prepare for next frame.
	mPreviousCount = mCurrentCount;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (mDeltaCount < 0)
	{
		mDeltaCount = 0;
	}
}