#pragma once
#include "TriggerTrap.h"

/**
 * 떨어지는 트리거 트랩. Falling이다. 소트오더는 낮다.
 */
class FallingTriggerTrap : public TriggerTrap
{
public:
	FallingTriggerTrap(float speed);
	
	virtual ~FallingTriggerTrap();

	Player* mGamePlayer;

	bool mTrigger;

	float mSpeed;

public:
	virtual void Update() override;
};