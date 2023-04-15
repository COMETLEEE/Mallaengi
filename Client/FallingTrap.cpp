#include "PreCompiledHeader.h"
#include "FallingTrap.h"

#include "Platform.h"

// 추락형 함정은 등속운동으로 떨어집니다.
#define MAX_FALLING_SPEED 6.f
#define PLUS_SPEED_PER_FRAME 0.18f
#define LR_COLUMN_COUNT 4

FallingTrap::FallingTrap(Vector2D startPos) :
	GameObject(),
	mIsTriggered(false),
	mPlatforms(std::vector<Platform*>(LR_COLUMN_COUNT)),
	mPlayer(nullptr)
{
	for (int i = 0; i < LR_COLUMN_COUNT; i++)
	{
		mPlatforms[i] = new Platform();

		Transform* transform = mPlatforms[i]->GetTransform();

		transform->SetPosition(startPos + Vector2D(TILE_WIDTH * i, 0.f));
	}
}

FallingTrap::~FallingTrap()
{
	
}

void FallingTrap::FixedUpdate()
{
	GameObject::FixedUpdate();

}

void FallingTrap::Update()
{
	GameObject::Update();

	if (mIsTriggered)
	{
		if (mFallingSpeed < MAX_FALLING_SPEED)
			mFallingSpeed += PLUS_SPEED_PER_FRAME;

		for (int i = 0; i < LR_COLUMN_COUNT; i++)
		{
			Platform* platform = mPlatforms[i];

			platform->GetTransform()->SetPosition(platform->GetTransform()->GetPosition() + mFallingSpeed * Vector2D::Down);
		}

		// Player가 아직 이 친구들과 충돌 중이면 좌표를 똑같이 줄여준다.
		for (int i = 0; i < LR_COLUMN_COUNT; i++)
		{
			Platform* platform = mPlatforms[i];

			std::vector<GameObject*> info = platform->GetCollision()->GetCollisionInfo();

			bool isChecked = false;

			for (GameObject* object : info)
			{
				// 플레이어와 아직 충돌 중이라면 ..
				if (object->GetTag() == "Player")
				{
					mPlayer->GetTransform()->SetPosition(mPlayer->GetTransform()->GetPosition() + mFallingSpeed * Vector2D::Down);

					isChecked = true;

					break;
				}
			}

			if (isChecked)
				break;
		}
	}
	else
	{
		for (int i = 0; i < LR_COLUMN_COUNT; i++)
		{
			Platform* platform = mPlatforms[i];

			std::vector<GameObject*> info = platform->GetCollision()->GetCollisionInfo();

			for (GameObject* object : info)
			{
				// 플레이어와 플랫폼의 윗판에서 충돌이 조금이라도 있었다면
				if ((object->GetTag() == "Player") && (platform->GetCollisionDir() == CollisionDir::UP))
				{
					// 트리거를 켜준다.
					mIsTriggered = true;

					mPlayer = object;
				}
			}
		}
	}
}