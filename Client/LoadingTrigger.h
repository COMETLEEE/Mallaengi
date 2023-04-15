#pragma once

/// <summary>
/// 트리거를 통해 씬 전환을 발생시키기 위한 클래스
/// 
/// 2022. 02. 22 JK
/// </summary>
class LoadingTrigger : public GameObject
{
	const std::string mTriggerSceneName;

public:
	LoadingTrigger(const string& triggerSceneName);
	~LoadingTrigger();

	virtual void Update() override;
};