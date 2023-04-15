#include "PreCompiledHeader.h"
#include "Restart.h"
#include "FadeOutObject.h"

Restart::Restart()
{
	mSize = { 143.f, 45.f };

	GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("OPTION_RESTART"));
}

Restart::~Restart()
{
}

void Restart::FixedUpdate()
{
	if (mIsActivated != true)
		return;

	ButtonBase::FixedUpdate();

	if (IsCursorOnButton())
		GetSpriteRenderer()->SetOpacity(0.5f);
	else
		GetSpriteRenderer()->SetOpacity(1.f);
}

void Restart::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	mIsClicked = true;

	// 페이드 아웃을 하고
	FadeOutObject* fade = new FadeOutObject(Game::GetInstance().GetCurrentScene()->GetSceneName());

	mFadeOut = fade;

	Game::GetInstance().GetCurrentScene()->AddGameObject(fade);

	Game::GetInstance().SetIsOptionClicked();
}