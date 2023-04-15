#pragma once

/**
 * 나초이지만 플레이어의 위치를 계속 감시하다가 본인의 x좌표 인근에 오면 라이징한다 ..! 맞으면 죽는다.
 *
 * 2022. 02. 18. Comet
 */
class RisingTrap : public GameObject
{
public:
	RisingTrap();
	virtual ~RisingTrap();

private:
	Player* mGamePlayer;

	bool mTrigger;

public:
	virtual void Update() override;
};