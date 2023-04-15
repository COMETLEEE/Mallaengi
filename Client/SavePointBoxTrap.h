#pragma once
#include "CheckPoint.h"
#include "ItemBox.h"

#define CREATE_TIME 3.f
#define MOVE_DELTA 1.5f


/**
 * \brief : 머리로 밑에서 찍으면 마요네즈 함정이 튀어나옴. (맞으면 죽음)
 */
 class SavePointBoxTrap : public ItemBox
{
 public:
	 // 킬링 마요네즈가 나오게 할 것이다.
	 SavePointBoxTrap(GameObject* object);
	 virtual ~SavePointBoxTrap();

	 bool mTrigger;

	// 일정 시간이 지나면 세이브 포인트를 생성하겠습니다.
	 float mTimer;

	 float mMoveDist;

	 bool mIsCreated;

	 bool mIsDone;

	 CheckPoint* mCheckPoint;

 public:
	virtual void TriggerEvent() override;

	virtual void Update() override;

	virtual void Release() override;
};