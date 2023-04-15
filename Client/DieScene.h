#pragma once


/**
 * 플레이어가 게임 플레이 중 죽었을 때 나오는 씬
 *
 * 2022. 02. 17. Comet
 */
class DieScene : public Scene
{
public:
	DieScene(std::string sceneName);
	virtual ~DieScene();

	// 죽은 스테이지의 이름
	std::string mStageName;

public:
	virtual void BuildScene() override;
};