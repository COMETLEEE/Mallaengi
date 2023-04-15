#include "PreCompiledHeader.h"
#include "StartButton.h"

#include "FadeOutObject.h"

StartButton::StartButton() :
mFadeOut(nullptr)
{
	// 스타트 버튼 이미지 내에서 진짜 버튼이 차지하고 있는 사이즈 적용
	mSize = { 429.f, 82.f };

	mNormalSprite = Game::GetInstance().GetResource()->GetSprite("INTRO_START");
	mOverSprite = Game::GetInstance().GetResource()->GetSprite("INTRO_START2");
}

StartButton::~StartButton()
{
	
}

void StartButton::FixedUpdate()
{
	if (mIsActivated != true)
		return;

	// 버튼이 눌렸다면
	if (mIsClicked)
	{
		if ((mFadeOut == nullptr) || (mFadeOut->GetSpriteRenderer()->GetOpacity() >= 1.0f))
		{
			
		}

		return;
	}

	if (IsCursorOnButton())
	{
		GetSpriteRenderer()->SetSprite(mOverSprite);
	}
	else
		GetSpriteRenderer()->SetSprite(mNormalSprite);
}

// 버튼이 클릭되었을 때 로드 !
void StartButton::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	if (Game::GetInstance().GetIsOptionOn())
		return;

	mIsClicked = true;

	FadeOutObject* fadeOut = new FadeOutObject("StageOneOpeningLoadingScene");
	//FadeOutObject* fadeOut = new FadeOutObject("OneEndingLoadingScene");

	mFadeOut = fadeOut;

	Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
}