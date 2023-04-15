#pragma once

#define DETECTING 30.f

/**
 * \brief : 플레이어가 같은 방향, 같은 y좌표에 있을 때 날아감
 */
class RedRight : public GameObject
{
public:
	RedRight(Vector2D dir, float moveSpeed);
	virtual ~RedRight();

	Player* mGamePlayer;

	Vector2D mDirrection;

	// 초당 몇 좌표 움직이실
	float mMoveSpeed;

	bool mTrigger;

public:
	virtual void Update() override;
};