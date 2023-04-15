#include "PreCompiledHeader.h"
#include "InfoButton.h"

InfoButton::InfoButton()
{
	// 인포 버튼 이미지 내에서 진짜 버튼이 차지하고 있는 사이즈 적용
	mSize = { 70.f, 70.f };
}

InfoButton::~InfoButton()
{
}

void InfoButton::FixedUpdate()
{
	if (mIsActivated != true)
		return;

	if (IsCursorOnButton())
	{
		// 이미지 바꿔라 ~
		// GetSpriteRenderer()->SetSprite();

		// 일단 투명도 조절
		GetSpriteRenderer()->SetOpacity(0.5f);
	}
	else
		GetSpriteRenderer()->SetOpacity(1.f);
}

void InfoButton::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	// 아무것도 안한다.
	Game::GetInstance().OptionToggle();
}