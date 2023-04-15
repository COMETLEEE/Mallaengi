#pragma once
#include "ButtonBase.h"

class FadeOutObject;

/**
 * Intro 화면에서 이 버튼을 누르면 게임이 시작됩니다.
 *
 * 2022. 02. 12. Comet
 */
class StartButton : public ButtonBase
{
public:
	StartButton();
	virtual ~StartButton();

private:
	// 버튼이 눌리고, Fade-In을 하면서 실행 !
	FadeOutObject* mFadeOut;

	Sprite* mNormalSprite;

	Sprite* mOverSprite;

public:

	virtual void FixedUpdate() override;
	virtual void OnButtonClicked() override;
};