#pragma once
#include "Scene.h"

class Intro : public Scene
{
public:
	Intro();
	virtual ~Intro();

public:
	virtual void BuildScene() override;
};