#pragma once
#include "ButtonBase.h"

/// <summary>
/// 볼륨 크기를 위해 만든 Progress Bar 클래스
/// 
/// 2022. 02. 24 JK
/// </summary>
class ProgressBar : public ButtonBase
{
	// 바의 진행 상태
	float mValue;
	float mMax;

	// Front Bar인지 확인
	bool mFront;

	// Bar가 변경됐을 때 호출할 함수 포인터
	void (*mFunc)(float Percent);

public:
	ProgressBar(Sprite* sprite, bool isFront, void (*func)(float Percent) = nullptr, float percent = 1.0f);
	~ProgressBar();
	
	virtual void Update() override;

	void SetPercent(float percent);

	void SetIncrease(float rate);
	void SetDecrease(float rate);
	virtual void OnButtonClicked() override;
};