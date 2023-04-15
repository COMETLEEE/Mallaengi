#include "PreCompiledHeader.h"
#include "FallingBlock.h"

#include "BlockBase.h"
#include "Platform.h"
#include "Player.h"

// 추락형 함정은 등속운동으로 떨어집니다.
#define MAX_FALLING_SPEED 3000.f
#define PLUS_SPEED_PER_FRAME 1000.f

FallingBlock::FallingBlock(Vector2D startPos, int columnCount) :
	GameObject(),
	mIsTriggered(false),
	mBlocks(std::vector<BlockBase*>(columnCount)),
	mGamePlayer(nullptr),
	mColumnCount(columnCount),
	mFallingSpeed(0.0f),
	mTimer(0.f)
{
	AddSpriteRenderer()->SetSortOrder(6);

	for (int i = 0; i < mColumnCount; i++)
	{
		mBlocks[i] = new BlockBase();

		Transform* transform = mBlocks[i]->GetTransform();

		transform->SetPosition(startPos + Vector2D(TILE_WIDTH * i, 0.f));

		Game::GetInstance().GetCurrentScene()->AddGameObject(mBlocks[i]);
	}

	mGamePlayer = Game::GetInstance().GetPlayer();
}

FallingBlock::~FallingBlock()
{

}

void FallingBlock::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void FallingBlock::Update()
{

}

void FallingBlock::LateUpdate()
{
	GameObject::LateUpdate();

	if (mIsTriggered)
	{
		float deltaTime = Timer::GetInstance().GetDeltaTime() / 1000.f;
		mTimer += deltaTime;

		if (mTimer >= 10.f)
		{
			for (int i = 0; i < mColumnCount; i++)
			{
				Game::GetInstance().GetCurrentScene()->ReserveDestroy(mBlocks[i]);
			}

			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);

			return;
		}

		if (mFallingSpeed < MAX_FALLING_SPEED)
			mFallingSpeed += PLUS_SPEED_PER_FRAME * deltaTime;

		mTransform->SetPosition(mTransform->GetPosition() + mFallingSpeed * Vector2D::Down * deltaTime);

		for (int i = 0; i < mColumnCount; i++)
		{
			BlockBase* platform = mBlocks[i];

			platform->GetTransform()->SetPosition(platform->GetTransform()->GetPosition() + mFallingSpeed * Vector2D::Down * deltaTime);
		}

		// Player가 아직 이 친구들과 충돌 중이면 좌표를 똑같이 줄여준다.
		for (int i = 0; i < mColumnCount; i++)
		{
			BlockBase* block = mBlocks[i];

			std::vector<GameObject*> info = block->GetCollision()->GetCollisionInfo();

			for (GameObject* object : info)
			{
				// 플레이어와 아직 충돌 중이라면 ..
				if (object->GetTag() == "Player")
				{
					//std::vector<GameObject*> info = mGamePlayer->GetCollision()->GetCollisionInfo();

					//for (GameObject* object2 : info)
					//{
					//	std::string tag = object2->GetTag();

					//	if (((tag == "BlockBase") || (tag == "Platform")) && (object2 != object))
					//	{
					//		isChecked = true;
					//	}
					//}

					/*if (!isChecked)
					{

					}*/

					mGamePlayer->GetTransform()->SetPosition(Vector2D(mGamePlayer->GetTransform()->GetPosition().mX, block->GetTransform()->GetPosition().mY - TILE_HEIGHT / 2 - (PLAYER_HEIGHT * PLAYER_SCALE / 2)));

					goto Escape;
				}
			}
		}

	Escape:;
	}
	else	// 평소에는 충돌 검사만 실시한다.
	{
		for (int i = 0; i < mColumnCount; i++)
		{
			BlockBase* block = mBlocks[i];

			std::vector<GameObject*> info = block->GetCollision()->GetCollisionInfo();

			for (GameObject* object : info)
			{
				// 플레이어와 플랫폼의 윗판에서 충돌이 조금이라도 있었다면
				if ((object->GetTag() == "Player") && (block->GetCollisionDir() == CollisionDir::UP))
					// 트리거를 켜준다.
					mIsTriggered = true;
			}
		}
	}
}