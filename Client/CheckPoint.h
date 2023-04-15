#pragma once

#define WEIGHT_DELTA 10.f

/**
 * CheckPoint, 여기를 먹으면 플레이어의 몸무게가 5 저장됩니다.
 *
 * 만약 죽게 된다면, 여기서 다시 소생해서 플레이를 계속 진행합니다.
 *
 * 2022. 02. 15. Comet
 */
class CheckPoint : public GameObject
{
public:
	CheckPoint();
	virtual ~CheckPoint();

	bool mTrigger;

public:
	virtual void Update() override;
};