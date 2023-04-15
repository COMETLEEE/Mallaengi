#pragma once

/**
 * \brief 감시하다가 플레이어가 본인 위를 지나가면 날아감 ~
 */
class UpperShuriken : public GameObject
{
public:
	UpperShuriken();
	virtual ~UpperShuriken();

private:
	Player* mGamePlayer;

	bool mTrigger;

public:
	virtual void Update() override;
};