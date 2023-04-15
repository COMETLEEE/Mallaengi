#pragma once

#define TIMER_ID	1000

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 델타 타임. 시간을 얻기 위한 클래스
/// </summary>
class Timer
{
private:
	Timer();
	Timer(const Timer& ref) {};
	Timer& operator=(const Timer& ref) {};
	~Timer();

public:
	static Timer& GetInstance()
	{
		static Timer instance;
		return instance;
	}


	int mStartTime;			// 측정 개시 시각
	int mSpriteCount;		// 카운터
	float mFps;				// fps
	const int mN = 60;		// 평균을 얻기 위한 샘플 값
	const int mFPS = 60;	// 설정하려는 fps

	// Quert . 교수님꺼 
private:
	__int64 mCountsPerSec;
	double mSecondsPerCount;

	__int64 mPreviousCount;
	__int64 mCurrentCount;
	__int64 mDeltaCount;
	double mDeltaTime;

public:
	float GetEngineTime();

	float GetDeltaTime();
	float GetFPS();

	void Update();
};