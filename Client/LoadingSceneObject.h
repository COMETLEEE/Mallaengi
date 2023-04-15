#pragma once

// 로딩 씬을 보여줄 시간을 컨트롤합니다.
#define GARA_LOADING_TIME 2.f

/// <summary>
/// 로딩 씬을 관리하는 Object. 시간을 체크해서 다음 씬으로 넘겨준다.
/// 
/// 또, 이미지 출력이 있을 경우 이 친구를 통해서 출력한다.
/// 
/// 2022. 02. 10. Comet
/// </summary>
class LoadingSceneObject : public GameObject
{
public:
	LoadingSceneObject(std::string nextSceneName);
	virtual ~LoadingSceneObject();

	std::string mNextSceneName;

	float mLoadTime;
	float mVolume;

public:
	virtual void FixedUpdate() override;

	virtual	void Update() override;
};