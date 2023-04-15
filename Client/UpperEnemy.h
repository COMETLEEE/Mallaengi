#pragma once
#include "FreeEnemy.h"

/**
 * \brief : 그냥 밑에 있다가 플레이어가 주변에 오면 튀어나와서 왼쪽으로 존나 달려가는 녀석
 *
 * 플레이어가 주변에 있는지 체킹하다가, 주변에 오면 좌상단으로 점프하는 느낌 ..?
 */
class UpperEnemy : public GameObject
{
public:
	UpperEnemy(std::string type);
	virtual ~UpperEnemy();

	Player* mGamePlayer;

	bool mTrigger;

	static float mTime;

	float mMyTime;

	std::string mType;
	
public:
	virtual void Update();
};