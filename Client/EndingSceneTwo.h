#pragma once

#include "Scene.h"

class EndingSceneTwo : public Scene
{
public:
	EndingSceneTwo();
	virtual ~EndingSceneTwo();

	virtual void BuildScene() override;
};