#pragma once
#include "Scene.h"

class StageTwo : public Scene
{
public:
	StageTwo();
	virtual ~StageTwo();

public:
	virtual void BuildScene() override;
};
