#pragma once
#include <random>
#include "Player.h"

#define KETCHAP_PLUS 0.5f

/**
 * \brief : 케찹. 날라다닌다.
 */
class Ketchap : public GameObject
{
public:
	Ketchap();
	virtual ~Ketchap();

	Vector2D mVelocity;

	bool mTrigger;

	float mGravity;

	Player* mGamePlayer;
	
	float mTimer;

	static std::random_device mRd;

	static std::mt19937 mMt;

	static std::uniform_int_distribution<int> mDistVelocityX;

	static std::uniform_int_distribution<int> mDistVelocityY;

public:
	virtual void Update() override;
};

// 얘가 생성될 때, 랜덤한 속도 (x,y : 적당한 범위 내에서) 를 가지고 생성되

// 그리고 매 업데이트마다 그 속도에 따라서 움직임

// 속도 중 y value는 매번 중력의 영향을 받음. 이러면 떨어질꺼야 곡선을 그리면서

// 근데, 만약, 플레이어랑 트리거가되면

// 투명해지면서 사라지고, 플레이어의 몸무게를 일정값 올리면됨.