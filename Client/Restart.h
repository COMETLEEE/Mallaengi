#pragma once
#include "ButtonBase.h"

class FadeOutObject;

class Restart : public ButtonBase
{
public:
	Restart();
	virtual ~Restart();

	FadeOutObject* mFadeOut;

private:
	virtual void FixedUpdate() override;

	virtual void OnButtonClicked() override;
};