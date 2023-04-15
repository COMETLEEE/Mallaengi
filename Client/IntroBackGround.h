#pragma once


/**
 * 스테이지마다 스크롤 속도, 스크롤 조건 다를 것으로 생각됨 ..
 *
 * 2022. 02. 16. Comet
 */
class IntroBackGround : public GameObject
{
public:
	IntroBackGround();
	virtual ~IntroBackGround();

public:
	virtual void LateUpdate() override;
};