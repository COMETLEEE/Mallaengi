#pragma once

class Platform;
/**
 * \brief 플레이어가 밟으면 추락하는 플랫폼
 *
 * 2022. 02. 21. Comet
 */
class FallingPlatform : public GameObject
{
public:
	FallingPlatform(Vector2D startPos);
	virtual ~FallingPlatform();

	bool mIsTriggered;					// 트리거 되었는지 변수

	Player* mGamePlayer;				// 트리거되면 여기에 플레이어를 저장합니다.

	Platform* mUpper;

	float mFallingSpeed;				// 떨어지는 속도를 컨트롤한다. 중력을 받는 것처럼 연출합니다.

	float mTimer;						// 일정 시간 지나면 없애야지

public:
	virtual void Update() override;
};