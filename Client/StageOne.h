#pragma once
#include "Scene.h"

class StageOne : public Scene
{
public:
	StageOne();
	virtual ~StageOne();

public:
	virtual void BuildScene() override;
};