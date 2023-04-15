#pragma once

#include "Player.h"
#define MOVE_DELTA 1.5f

// ´êÀ¸¸é Á×´Â ¸¶¿ä³×Áî, SavePointBoxTrap¿¡¼­ ³ª¿È
//
// 2022. 02. 22. Comet
class KillMayo : public GameObject
{
public:
	KillMayo();
	virtual ~KillMayo();

	float mMoveDist;

	bool mIsDone;

	float mVelocityY;

	float mTimer;

public:
	virtual void Update() override;
};