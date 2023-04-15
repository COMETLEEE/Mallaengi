#pragma once

/**
 * 씬을 Load하고 Build될 때 Fade-In을 담당합니다.
 *
 * 2022. 02. 16. Comet
 */
class FadeInObject : public GameObject
{
public:
	FadeInObject();
	virtual ~FadeInObject();

private:
	// 페이딩 시간
	float mFadeTime;

public:
	virtual void Update() override;
};