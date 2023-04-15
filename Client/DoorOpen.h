#pragma once
#include "ItemBox.h"


class TriggerTrap;

class DoorOpen : public ItemBox
{
public:
	DoorOpen();
	virtual ~DoorOpen();

private:
	std::vector<TriggerTrap*> mTriggerTraps;

	bool mIsDone;

public:
	virtual void Update() override;

	std::vector<TriggerTrap*> GetTriggerTraps() { return mTriggerTraps; }
};