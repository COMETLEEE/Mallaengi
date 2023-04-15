#pragma once
#include "BlockBase.h"

class Niddle : public BlockBase
{
public:
	Niddle(CollisionDir dir);

	virtual ~Niddle();

	CollisionDir mDetectWay;

	bool mIsDone;

public:
	virtual void Update() override;
};