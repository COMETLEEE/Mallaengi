#pragma once

#include "BlockBase.h"

#define MOVE_SPEED 300.f

/// <summary>
/// Riding Nacho : 타고 올라가는 나초
/// 
/// 2022. 02. 24. Comet
/// </summary>
class RidingNacho : public BlockBase
{
public:
	RidingNacho();
	virtual ~RidingNacho();

	bool mTrigger;

	bool mIsDone;

	float mMoveDistance;

	float mTimer;

public:
	virtual void Update() override;
};