#pragma once
#include "ButtonBase.h"


class InfoButton : public ButtonBase
{
public:
	InfoButton();
	virtual ~InfoButton();

public:

	virtual void FixedUpdate() override;
	virtual void OnButtonClicked() override;
};
