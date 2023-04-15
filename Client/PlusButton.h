#pragma once

#include "ButtonBase.h"

class ProgressBar;

class PlusButton : public ButtonBase
{
private:
	ProgressBar* mRoot;

public:
	PlusButton(ProgressBar* root);
	virtual ~PlusButton();

	virtual void FixedUpdate() override;
	virtual void OnButtonClicked() override;
};