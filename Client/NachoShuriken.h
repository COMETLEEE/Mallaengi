#pragma once
#include "TriggerTrap.h"
#include "Player.h"


/**
 * \brief : 애니메이션을 들고 있는 나초 수리검이다.
 *
 * 2022. 02. 22. Comet
 */
class NachoShuriken : public GameObject
{
public:
	NachoShuriken(Vector2D dir);
	virtual ~NachoShuriken();

	// 수리검이 날아갈 방향
	Vector2D mDirrection;



	AnimationClip* mAnimation;

public:
	virtual void Update() override;
};