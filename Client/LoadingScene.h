#pragma once
#include "Scene.h"

/// <summary>
/// 여기서 진짜 다음 스테이지에 있는 것들을 미리 로드하는게 좋을 것 같기도 .. (Scene을 New하는 것)
/// 
/// 2022. 02. 10.
/// </summary>
class LoadingScene : public Scene
{
public:
	LoadingScene(std::string nextSceneName);
	virtual ~LoadingScene();

	std::string mLoadSceneName;

public:
	void BuildScene() override;
};