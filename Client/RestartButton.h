#pragma once
#include "ButtonBase.h"

class RestartButton : public ButtonBase
{
public:
	RestartButton(std::string sceneName);
	virtual ~RestartButton();

private:
	std::string mSceneName;

public:
	virtual void FixedUpdate() override;

	virtual void OnButtonClicked() override;
};