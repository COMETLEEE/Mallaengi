#pragma once

#include "Scene.h"

class EndingSceneOne : public Scene
{
public:
	EndingSceneOne();
	virtual ~EndingSceneOne();

	virtual void BuildScene() override;
};