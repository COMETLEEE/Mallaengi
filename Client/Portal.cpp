#include "PreCompiledHeader.h"
#include "Portal.h"

#include "FadeOutObject.h"
#include "Player.h"

Portal::Portal() :
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mTrigger(false),
	mTimer(0.f),
	mIsDone(false)
{
	AddSpriteRenderer()->SetSortOrder(5);
}

Portal::~Portal()
{

}

void Portal::Update()
{
	Vector2D myPos = mTransform->GetPosition();

	Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

	// 적당히 근처에서 위 화살표 키 누르면
	if (((abs(myPos.mX - playerPos.mX) <= PLAYER_WIDTH * PLAYER_SCALE / 2 + 15.f) &&
		 ((playerPos.mY <= myPos.mY + 200.f) && (playerPos.mY >= myPos.mY - 200.f))) && (Input::GetInstance().GetKeyState(VK_UP) == KEYSTATE::DOWN))
		mTrigger = true;

	if (mTrigger)
	{
		SpriteRenderer* spri = mGamePlayer->GetSpriteRenderer();

		if ((spri->GetOpacity() > 0.f))
			spri->SetOpacity(spri->GetOpacity() - 0.02f);
		else if (spri->GetOpacity() <= 0.f)
		{
			float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

			mTimer += delta;

			if ((mTimer >= 1.5f) && (!mIsDone))
			{
				std::string sceneName = Game::GetInstance().GetCurrentScene()->GetSceneName();

				if (sceneName == "StageOne")
				{
					std::string reserve = "StageTwoOpeningLoadingScene";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}
				else if (sceneName == "StageTwo")
				{
					std::string reserve = "StageThreeOneOpeningLoadingScene";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}
				else if (sceneName == "StageThreeFive")
				{
					std::string reserve = "EndingTwoLoadingScene";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}

				mIsDone = true;
			}
		}

		static bool once = true;

		if (once == true)
		{
			once = false;
			SoundManager::GetInstance()->Play(500033);
		}
	}
}