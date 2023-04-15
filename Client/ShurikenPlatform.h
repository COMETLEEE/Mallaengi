#pragma once
#include "BlockPlatform.h"

/**
 * \brief : 밟으면 오른쪽 일정 distance에서 나초 수리검이 날아옴
 *
 * 2022. 02. 22. Comet
 */
class ShurikenPlatform : public BlockPlatform
{
public:
	ShurikenPlatform();
	virtual ~ShurikenPlatform();

	bool mTrigger;

public:
	virtual void Update() override;
};