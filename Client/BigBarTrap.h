#pragma once
#include "ItemBox.h"
#include "Portal.h"

class BigBarTrap : public ItemBox
{
public:
	BigBarTrap(GameObject* reserve);
	virtual ~BigBarTrap();

	GameObject* mBigBar;

	Player* mGamePlayer;

	Portal* mPortal;

	bool mIsChecked;

	bool mUpdated;

public:
	virtual void Update() override;
	virtual void Release() override;
};
