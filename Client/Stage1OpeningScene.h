#pragma once

#include "Scene.h"

/// <summary>
/// 스테이지 1 시작할 때 나오는 내러티브 씬
/// 
/// 2022. 02. 24 JK
/// </summary>
class Stage1OpeningScene : public Scene
{
public:
	Stage1OpeningScene();
	virtual ~Stage1OpeningScene();

	virtual void BuildScene() override;
};