#pragma once

/// <summary>
/// 내러티브 이미지 출력을 위한 객체
/// 
/// 2022. 02. 23
/// </summary>
class NarrativeSprite : public GameObject
{
	double mDelay;			// 생성 후 지연 시간
	double mDuration;		// 출력 시간
	int mAlphaSpeed;		// 알파 전환 속도
	float mAlpha;			// 출력 알파값
	bool  mNext;			// 출력 후 전환시에 사용할 변수

public:
	NarrativeSprite(Sprite* sprite, double delay, double duration, int speed);
	virtual ~NarrativeSprite();

	virtual void Update() override;
};