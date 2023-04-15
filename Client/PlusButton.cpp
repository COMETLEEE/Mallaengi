#include "PreCompiledHeader.h"
#include "PlusButton.h"
#include "ProgressBar.h"

PlusButton::PlusButton(ProgressBar* root)
	: mRoot(root)
{

}

PlusButton::~PlusButton()
{

}

void PlusButton::FixedUpdate()
{
	if (mIsActivated != true)
		return;

	ButtonBase::FixedUpdate();

	if (IsCursorOnButton())
	{
		GetSpriteRenderer()->SetOpacity(0.5f);
	}
	else
		GetSpriteRenderer()->SetOpacity(1.f);
}

void PlusButton::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	// if (mRoot != nullptr)
		// mRoot->
}