#pragma once

/**
 * 각 스테이지에서 배경화면을 출력하는데 사용할 Object
 *
 * 2022. 02. 15. Comet. 그냥 껍데기다.
 */
class StageOneBackGround : public GameObject
{
public:
	StageOneBackGround();
	virtual ~StageOneBackGround();

public:
	virtual void LateUpdate() override;
};