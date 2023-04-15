#pragma once

#include "BlockBase.h"
#include "FiveFalling.h"

/**
 * \brief : 트리거 도어. 3-5 스테이지서 모든 오브젝트 추락 후 열립니다.
 *
 * 2022. 02. 25. Comet
 */
class TriggerDoor : public BlockBase
{
public:
	TriggerDoor();
	virtual ~TriggerDoor();

	float mTotalWait;

public:
	virtual void Update() override;
};