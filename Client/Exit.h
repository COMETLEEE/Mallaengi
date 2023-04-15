#pragma once
#include "ButtonBase.h"

class Exit : public ButtonBase
{
public:
	Exit();
	virtual ~Exit();

private:
	virtual void FixedUpdate() override;
	
	virtual void OnButtonClicked() override;
};