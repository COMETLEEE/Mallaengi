#pragma once
#include "Player.h"

#define DELETE_TIME 1.5f

/// <summary>
/// 주변에 플레이어가 오면 (1.5 tile) 상승, 닿으면 죽음
/// 
/// 1.5초뒤 삭제. 2022. 02. 24. Comet
/// </summary>
class SlowNiddle : public GameObject
{
public:
	SlowNiddle();

	virtual ~SlowNiddle();

private:
	bool mTrigger;

	Player* mGamePlayer;

	float mTimer;

public:
	virtual void Update() override;
};