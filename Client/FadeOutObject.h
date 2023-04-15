#pragma once


/// <summary>
/// 씬이 종료가 될 때 Fade-Out을 실시하는 오브젝트
///
///	2022. 02. 16. Comet
/// </summary>
class FadeOutObject : public GameObject
{
public:
	FadeOutObject();
	FadeOutObject(std::string sceneName);
	virtual ~FadeOutObject();

private:
	float mFadeTime;

	// 페이드 아웃이 끝나고 로드할 씬 이름
	std::string mSceneName;

	bool mIsWantLoadScene;

	// 타이틀 화면으로 ..?
	bool mIsTitle;

	float mVolume;

public:
	virtual void Update() override;
};