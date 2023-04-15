#include "PreCompiledHeader.h"
#include "FallingPlatform.h"

#include "Platform.h"
#include "Player.h"

// 추락형 함정은 등속운동으로 떨어집니다.
#define MAX_FALLING_SPEED 3000.f
#define PLUS_SPEED_PER_FRAME 550.f

FallingPlatform::FallingPlatform(Vector2D startPos) :
	mIsTriggered(false),
	mGamePlayer(nullptr),
	mFallingSpeed(0.0f)
{
	AddSpriteRenderer()->SetSortOrder(6);

	mUpper = new Platform();

	mUpper->GetTransform()->SetPosition(startPos);

	Game::GetInstance().GetCurrentScene()->AddGameObject(mUpper);

	mGamePlayer = Game::GetInstance().GetPlayer();
}

FallingPlatform::~FallingPlatform()
{
}

void FallingPlatform::Update()
{
	GameObject::Update();

	if (mIsTriggered)
	{
		float deltaTime = Timer::GetInstance().GetDeltaTime() / 1000.f;
		mTimer += deltaTime;

		if (mTimer >= 10.f)
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);

		if (mFallingSpeed < MAX_FALLING_SPEED)
			mFallingSpeed += PLUS_SPEED_PER_FRAME * deltaTime;

		mTransform->SetPosition(mTransform->GetPosition() + mFallingSpeed * Vector2D::Down * deltaTime);

		mUpper->GetTransform()->SetPosition(mUpper->GetTransform()->GetPosition() + mFallingSpeed * Vector2D::Down * deltaTime);

		std::vector<GameObject*> info = mUpper->GetCollision()->GetCollisionInfo();
		
		for (GameObject* object : info)
		{
			// 플레이어와 아직 충돌 중이라면 ..
			if (object->GetTag() == "Player")
			{
				mGamePlayer->GetTransform()->SetPosition(Vector2D(mGamePlayer->GetTransform()->GetPosition().mX, mUpper->GetTransform()->GetPosition().mY - TILE_HEIGHT / 2 - (PLAYER_HEIGHT * PLAYER_SCALE / 2)));

				break;
			}
		}
	}
	else
	{
		std::vector<GameObject*> info = mUpper->GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			// 플레이어와 플랫폼의 윗판에서 충돌이 조금이라도 있었다면
			if ((object->GetTag() == "Player") && (mUpper->GetCollisionDir() == CollisionDir::UP))
				// 트리거를 켜준다.
				mIsTriggered = true;
		}
	}
}