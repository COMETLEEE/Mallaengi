#pragma once
#include "Scene.h"

class StageThree : public Scene
{
public:
	StageThree();
	virtual ~StageThree();

public:
	virtual void BuildScene() override;
};