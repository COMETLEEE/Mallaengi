#pragma once

#include "Scene.h"

/// <summary>
/// 스테이지 3 시작할 때 나오는 내러티브 씬
/// 
/// 2022. 02. 24 JK
/// </summary>
class Stage3OpeningScene : public Scene
{
public:
	Stage3OpeningScene();
	virtual ~Stage3OpeningScene();

	virtual void BuildScene() override;
};