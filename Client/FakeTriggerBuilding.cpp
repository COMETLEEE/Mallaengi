#include "PreCompiledHeader.h"
#include "FakeTriggerBuilding.h"

#include "Player.h"

#define ROCKET_SPEED 700.f

FakeTriggerBuilding::FakeTriggerBuilding() :
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mTrigger(false),
	mTimer(0.f),
	mLastLoop(false)
{
	AddSpriteRenderer()->SetSortOrder(6);
}

FakeTriggerBuilding::~FakeTriggerBuilding()
{
}

void FakeTriggerBuilding::Update()
{
	GameObject::Update();

	Vector2D myPos = mTransform->GetPosition();

	Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

	// 적당히 근처에서 위에키 누르면
	if (((abs(myPos.mX - playerPos.mX) <= PLAYER_WIDTH * PLAYER_SCALE / 2 + 15.f) &&
		(playerPos.mY >= myPos.mY + 100.f)) && (Input::GetInstance().GetKeyState(VK_UP) == KEYSTATE::DOWN))
		mTrigger = true;

	if (mTrigger)
	{
		SpriteRenderer* spri = mGamePlayer->GetSpriteRenderer();
		
		if ((spri->GetOpacity() > 0.f) && (!mLastLoop))
			spri->SetOpacity(spri->GetOpacity() - 0.005f);
		else if (spri->GetOpacity() <= 0.f)
		{
			float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

			mTimer += delta;

			mTransform->SetPosition(myPos + delta * ROCKET_SPEED * Vector2D::Up);

			//로켓
			if (SoundManager::GetInstance()->Playing(500022) != true)
			{
				SoundManager::GetInstance()->Play(500022);
			}
		}
		
		
		if (mTimer >= 3.f)
		{
			mLastLoop = true;

			mGamePlayer->SetHp(0);
		}
	}
}
