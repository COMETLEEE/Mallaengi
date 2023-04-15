#pragma once

/**
 * Intro / Loading Scene에서 사용될 카메라입니다. (정중앙 고정)
 *
 * 2022. 02. 12. Comet
 */
class SubCamera : public GameObject
{
public:
	SubCamera();
	virtual ~SubCamera();

public:
	virtual void LateUpdate() override;
};