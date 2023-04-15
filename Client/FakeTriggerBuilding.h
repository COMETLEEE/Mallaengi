#pragma once

class Player;

/**
 * \brief 페이크 트리거 빌딩 .. 문에서 윗방향키를 누르면
 *
 * // 플레이어 소멸시키고 공중으로 ㅃㅇ. 3초정도 후, SetOpacity 하고 -> SetHp(0)
 *
 * // 2022. 02. 21. Comet
 */
class FakeTriggerBuilding : public GameObject
{
public:
	FakeTriggerBuilding();
	virtual ~FakeTriggerBuilding();

	Player* mGamePlayer;

	bool mTrigger;

	float mTimer;

	bool mLastLoop;
public:
	virtual void Update() override;
};