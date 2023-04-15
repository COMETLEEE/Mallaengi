#pragma once
#include "ButtonBase.h"

class FadeOutObject;

class Title : public ButtonBase
{
public:
	Title();
	virtual ~Title();

private:

	virtual void FixedUpdate() override;
	virtual void OnButtonClicked() override;
};