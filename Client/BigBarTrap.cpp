#include "PreCompiledHeader.h"
#include "BigBarTrap.h"

#include "DecoObject.h"
#include "Player.h"
#include "Portal.h"

BigBarTrap::BigBarTrap(GameObject* reserve):
	ItemBox(reserve, 2),
	mIsChecked(false),
	mUpdated(false),
	mBigBar(nullptr),
	mPortal(nullptr)
{
	GameObject* BigBar = new DecoObject();

	BigBar->GetSpriteRenderer()->SetSortOrder(4);

	BigBar->GetSpriteRenderer()->SetSprite(new Sprite(20108, Vector2D(0.5f, 0.5f), {320.f, 157.f}, 0.f, Vector2D(720.f, 160.f)));

	mBigBar = BigBar;

	mBigBar->GetSpriteRenderer()->SetOpacity(0.f);

	mGamePlayer = Game::GetInstance().GetPlayer();

	mPortal = new Portal();

	mPortal->GetSpriteRenderer()->SetSprite(new Sprite(20108, Vector2D(0.5f, 0.5f), { 320.f, 397.f }, 0.f, Vector2D(400.f, 803.f)));

	//Vector2D(24000.f - 4 * TILE_WIDTH, 4 * TILE_HEIGHT); 뭔지 몰라서 일단 주석
}

BigBarTrap::~BigBarTrap()
{
}

void BigBarTrap::Update()
{
	ItemBox::Update();

	if (!mUpdated)
	{
		mPortal->GetTransform()->SetPosition(mTransform->GetPosition() + Vector2D(27.5 * TILE_WIDTH, 4 * TILE_HEIGHT));

		Game::GetInstance().GetCurrentScene()->AddGameObject(mPortal);

		mUpdated = true;
	}

	// 트리거가 되었다면 거대 말랭바를 떨어뜨리고, 포탈도 추락시킨다.
	if ((mTrigger) && (!mIsChecked))
	{
		mBigBar->GetTransform()->SetPosition(mTransform->GetPosition() + Vector2D(TILE_WIDTH * 27.5f, - TILE_HEIGHT * 8.f));

		// 플레이어의 y좌표가 BigBar 좌표랑 비슷해지면 가는거야.
		if (abs(mBigBar->GetTransform()->GetPosition().mY - mGamePlayer->GetTransform()->GetPosition().mY) <= 50.f)
		{
	 		mIsChecked = true;	// 체킹 완료. 떨어지자.

			Game::GetInstance().GetCurrentScene()->AddGameObject(mBigBar);
		}
	}

	if (mIsChecked)
	{
		static float timer = 0.f;

		mBigBar->GetSpriteRenderer()->SetOpacity(mBigBar->GetSpriteRenderer()->GetOpacity() + 0.02f);

		if (mBigBar->GetSpriteRenderer()->GetOpacity() >= 1.f)
		{
			float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

			timer += delta;

			Transform* bigTransform = mBigBar->GetTransform();

			bigTransform->SetPosition(bigTransform->GetPosition() + delta * 1000.f* Vector2D::Down);

			// 이 떄부터, 포탈도 추락시킨다.
			if (timer >= 0.8f)
			{
				mPortal->GetTransform()->SetPosition(mPortal->GetTransform()->GetPosition() + delta * 1000.f * Vector2D::Down);
			}
		}
	}
}

void BigBarTrap::Release()
{
	ItemBox::Release();

	if (mBigBar != nullptr)
		delete mBigBar;
}