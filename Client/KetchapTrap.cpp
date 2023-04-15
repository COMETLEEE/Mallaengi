#include "PreCompiledHeader.h"
#include "KetchapTrap.h"

#include <random>
#include <ctime>
#include <iostream>

#include "Ketchap.h"
#include "Player.h"

// 케찹이 올라오는 속도
#define RISING_DELTA_X 10.f
#define RISING_SPEED_PER_SEC 2700.f

KetchapTrap::KetchapTrap() :
	mTrigger(false),
	mVelocity(Vector2D::Zero),
	mGravity(GRAVITY),
	mCreateTime(1.f),
	mTimer(0.f)
{
	// 플레이어 받아오기
	mGamePlayer = Game::GetInstance().GetPlayer();

	AddAABBCollision();

	AddSpriteRenderer()->SetSortOrder(5);
}

KetchapTrap::~KetchapTrap()
{
}

void KetchapTrap::Update()
{
	GameObject::Update();

	Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

	Vector2D myPos = mTransform->GetPosition();

	if (abs(playerPos.mX - myPos.mX) > 4000.f)
		return;

	std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

	for (GameObject* object : info)
	{
		if (object->GetTag() == "Player")
			mTrigger = true;
	}

	if (mTrigger)
		mCreateTime = 0.2f;

	float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

	mTimer += delta;

	if (mTimer >= mCreateTime)
	{
		Ketchap* ket = new Ketchap();

		ket->GetTransform()->SetPosition(mTransform->GetPosition() + Vector2D(TILE_WIDTH * 5, TILE_HEIGHT * 2));

		Game::GetInstance().GetCurrentScene()->AddGameObject(ket);

		mTimer = 0.f;
	}
}
