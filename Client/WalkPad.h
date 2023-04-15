#pragma once

#define WALKPAD_SPEED_PER_SEC 250.f
#include "BlockBase.h"

/**
 * \brief : 밟고 있으면 설정된 방향으로 가속 ..!
 *
 * 2022. 02. 23. Comet
 */
class WalkPad : public GameObject
{
public:
	WalkPad(Vector2D dir);
	virtual ~WalkPad();

private:
	Vector2D mDirrection;

	Player* mGamePlayer;

	static bool mPlayerChecked;

	static bool mMonsterChecked;

	static bool mIsDoen;

public:

	virtual void FixedUpdate() override;
	virtual void Update() override;
};