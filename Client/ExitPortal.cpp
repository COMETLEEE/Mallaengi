#include "PreCompiledHeader.h"
#include "ExitPortal.h"

#include "FadeOutObject.h"
#include "Player.h"

ExitPortal::ExitPortal() :
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mTrigger(false),
	mTimer(0.f),
	mIsDone(false)
{
	AddSpriteRenderer()->SetSortOrder(5);
}

ExitPortal::~ExitPortal()
{

}

void ExitPortal::Update()
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

				if (sceneName == "StageThreeOne")
				{
					std::string reserve = "StageThreeTwo";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}
				else if (sceneName == "StageThreeTwo")
				{
					std::string reserve = "StageThreeThree";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}
				else if (sceneName == "StageThreeThree")
				{
					std::string reserve = "StageThreeFour";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}
				else if (sceneName == "StageThreeFour")
				{
					std::string reserve = "StageThreeFive";

					Game::GetInstance().GetCurrentScene()->ReserveCreate(new FadeOutObject(reserve));
				}
				else if (sceneName == "StageThreeFive")
				{
					/// 최종 몸무게에 따른 if문

					float lastBodyWeight = Game::GetInstance().GetLastBodyWeight();

					if (lastBodyWeight >= 100.f)
					{
						FadeOutObject* fadeOut = new FadeOutObject("OneEndingLoadingScene");

						Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
					}
					else if (lastBodyWeight < 100.f)
					{
						FadeOutObject* fadeOut = new FadeOutObject("TwoEndingLoadingScene");

						Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
					}
				}

				mIsDone = true;
			}
		}
	}
}