#pragma once

/**
 * Json File 입, 출력을 실험하기 위한 Scene
 *
 * 2022. 02. 15. Comet
 */
class CometScene : public Scene
{
public:
	CometScene();
	virtual ~CometScene();

public:
	virtual void BuildScene() override;
};