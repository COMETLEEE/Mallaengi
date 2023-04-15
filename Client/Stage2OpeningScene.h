#pragma once

#include "Scene.h"

/// <summary>
/// 스테이지 2 시작할 때 나오는 내러티브 씬
/// 
/// 2022. 02. 24 JK
/// </summary>
class Stage2OpeningScene : public Scene
{
public:
	Stage2OpeningScene();
	virtual ~Stage2OpeningScene();

	virtual void BuildScene() override;
};