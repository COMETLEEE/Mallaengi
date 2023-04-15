#pragma once
#include "BlockPlatform.h"


/**
 * \brief : 지면을 감지하여 만약, 밟히면 위에서 에너미를 추락시킨다.
 */
class FallingEnemy : public BlockPlatform
{
public:
	FallingEnemy();
	virtual ~FallingEnemy();

	bool mTrigger;

public:
	virtual void Update() override;
};