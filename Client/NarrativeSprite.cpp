#include "PreCompiledHeader.h"
#include "NarrativeSprite.h"

#include "FadeOutObject.h"

NarrativeSprite::NarrativeSprite(Sprite* sprite, double delay, double duration, int speed)
	: mDelay(delay)
	, mDuration(duration)
	, mAlphaSpeed(speed)
	, mAlpha(0.0f)
	, mNext(false)
{
	AddSpriteRenderer()->SetSprite(sprite);
	GetSpriteRenderer()->SetOpacity(mAlpha);
}

NarrativeSprite::~NarrativeSprite()
{

}

void NarrativeSprite::Update()
{
	// 지연 시간이 되기 전에는 출력하지 않는다.
	if (mDelay <= 0.0f)
	{
		// 지속 시간이 끝나면
		if (mDuration <= 0.0f)
		{
			// 알파값을 감소하여 Fade Out 효과 적용
			if (mAlphaSpeed > 0)
			{
				mAlpha -= (Timer::GetInstance().GetDeltaTime() / 2000.0f) * mAlphaSpeed;
				GetSpriteRenderer()->SetOpacity(mAlpha);
			}

			// 알파값이 0이하가 되면 오브젝트를 제거
			if (mAlpha <= 0.0f || mAlphaSpeed <= 0)
			{
				Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);

				// 마지막 컷씬인 경우 스테이지 시작
				if (GetSpriteRenderer()->GetSprite()->mSpriteSheetIndex == 10210)
				{
					FadeOutObject* fadeOut = new FadeOutObject("StageOneLoadingScene");

					Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
				}
				else if (GetSpriteRenderer()->GetSprite()->mSpriteSheetIndex == 10304)
				{
					FadeOutObject* fadeOut = new FadeOutObject("StageTwoLoadingScene");

					Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
				}
				else if (GetSpriteRenderer()->GetSprite()->mSpriteSheetIndex == 10415)
				{
					FadeOutObject* fadeOut = new FadeOutObject("StageThreeOneLoadingScene");

					Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
				}
				else if (GetSpriteRenderer()->GetSprite()->mSpriteSheetIndex == 10508
					|| GetSpriteRenderer()->GetSprite()->mSpriteSheetIndex == 10607)
				{
					FadeOutObject* fadeOut = new FadeOutObject("IntroLoadingScene");

					Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
				}
			}
		}
		// 지속중이면
		else
		{
			// 알파값을 증가하여 Fade In 효과 적용
			if (mAlphaSpeed > 0)
			{
				mAlpha += (Timer::GetInstance().GetDeltaTime() / 2000.0f) * mAlphaSpeed;

				// 1까지만
				if (mAlpha > 1.0f)
				{
					mAlpha = 1.0f;

					if (GetSpriteRenderer()->GetSprite()->mSpriteSheetIndex == 10607)
					{
						Vector2D pos = GetTransform()->GetPosition();

						if (pos.mX > Graphics::GetInstance().GetScreenSize().width / 2)
							GetTransform()->SetPosition(pos - Vector2D(100.0f, 0) * Timer::GetInstance().GetDeltaTime() / 1000);
					}
				}

				GetSpriteRenderer()->SetOpacity(mAlpha);
			}
			else
			{
				GetSpriteRenderer()->SetOpacity(1.0f);
			}

			mDuration -= Timer::GetInstance().GetDeltaTime() / 1000;
		}
	}
	else
	{
		mDelay -= Timer::GetInstance().GetDeltaTime() / 1000;
	}
}