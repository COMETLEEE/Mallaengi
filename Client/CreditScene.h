#pragma once

#include "Scene.h"

class CreditScene : public Scene
{
public:
	CreditScene();
	virtual ~CreditScene();

	virtual void BuildScene() override;
};