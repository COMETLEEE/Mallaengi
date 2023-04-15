#pragma once
#include "ButtonBase.h"

class Back : public ButtonBase
{
public:
	Back();
	virtual ~Back();

private:
	virtual void FixedUpdate() override;
	
	virtual void OnButtonClicked() override;
};