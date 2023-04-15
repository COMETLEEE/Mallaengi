#pragma once 
#include "FreeEnemy.h"

#define SEARCH_DIST 1500.f

/**
 * \brief : 왼쪽에 플레이어가 있으면, 빠르게 달려온다 ?!
 *
 * 2022. 02. 23. Comet
 */
class OneWayMob : public EnemyBase
{
public:
	OneWayMob(std::string type, float moveSpeed, Vector2D Dir = Vector2D(-1.f, 0.f));
	~OneWayMob() override;

protected:
	std::string mType;

	float mMoveSpeed;

	Vector2D mDirrection;

	Player* mGamePlayer;

public:

	virtual void Idle() override;

	virtual void Run() override;

	virtual void Die() override;

	virtual void LoadAnimationProcess() override;
};