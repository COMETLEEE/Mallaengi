#pragma once

class OneWayMob;

/**
 * \brief : 만약 플레이어가 일정한 같은 방향에 있으면 원웨이몹을 스폰시킴.
 *
 * 2022. 02. 23. Comet
 */
class OneWayMobTrigger : public GameObject
{
public:
	OneWayMobTrigger(std::string type, float moveSpeed, Vector2D Dir = Vector2D(-1.0f, 0.f));
	virtual ~OneWayMobTrigger();

private:
	bool mTrigger;

	OneWayMob* mReserve;

	Player* mGamePlayer;

	Vector2D mDirrection;

	bool mIsDone;
public:

	virtual void Update() override;
};