#include "PreCompiledHeader.h"
#include "Back.h"

Back::Back()
{
	mSize = { 148.f , 45.f };

	GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("OPTION_BACK"));
}

Back::~Back()
{
}

void Back::FixedUpdate()
{
	if (mIsActivated != true)
		return;

	ButtonBase::FixedUpdate();

	if (IsCursorOnButton())
		GetSpriteRenderer()->SetOpacity(0.5f);
	else
		GetSpriteRenderer()->SetOpacity(1.f);
}

void Back::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	// 옵션을 꺼준다.
	Game::GetInstance().SetIsOptionClicked();
}