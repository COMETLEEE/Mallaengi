#include "PreCompiledHeader.h"
#include "Exit.h"

Exit::Exit()
{
	mSize = {146.f, 45.f};

	GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("OPTION_EXIT"));
}

Exit::~Exit()
{
}

void Exit::FixedUpdate()
{
	if (mIsActivated != true)
		return;

	ButtonBase::FixedUpdate();

	if (IsCursorOnButton())
		GetSpriteRenderer()->SetOpacity(0.5f);
	else
		GetSpriteRenderer()->SetOpacity(1.f);
}

void Exit::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	Game::GetInstance().SetIsOptionClicked();

	Game::GetInstance().EndGame();
}