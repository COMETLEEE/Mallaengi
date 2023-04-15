#pragma once

#define DETECTING 30.f


/// <summary>
/// 플레이어가 같은 방향, 같은 x좌표에 있을때 돌진
/// 
/// 2022. 02. 24. Comet
/// </summary>
class RedUp : public GameObject
{
public:
	RedUp(Vector2D dir, float moveSpeed);
	RedUp(Vector2D dir, float moveSpeed, float lengthDetection);

	virtual ~RedUp();

	Vector2D mDirrection;

	Player* mGamePlayer;

	// 초당 몇 좌표 움직이실
	float mMoveSpeed;

	bool mHasLength;

	float mLengthDetection;

	bool mTrigger;

public:
	virtual void Update() override;
};