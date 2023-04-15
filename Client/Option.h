#pragma once


/**
 * GameLoop에 있는 것으로 합시다 ..
 */
class Option : public GameObject
{
public:
	Option();
	virtual ~Option();

public:

	virtual void Update();
};

// 1. esc 버튼을 누른다 (아무튼 버튼)

// 2. 누르면 Game 내에 있던 Option 객체가 CurrentScene에 ReserveCreate() 됩니다.

// 3 - 1. Option이 나와 있으면 다른 녀석들의 Update를 모두 멈춘다. (옵션만 업데이트)

// 3 - 2. 버튼 4개가 있음 -> 각각의 버튼에 따른 이벤트를 실시한다.

// 1. 종료하기 : 그냥 꺼버림 endgame == true

// 2. 그만하기 : player 정보 리셋하고 Intro로 이동

// 3. 계속하기 : 옵션창 끄고 다시 모든 것들의 Update를 시작한다.

// 4. 다시하기 : UI만 업데이트 중인데 .. FadeOUt하고 -> ReserveLoadScene(mCurrenetScene->GetSceneName()) ..?


// 3. 그럼 다음 프레임에서 Option이 나오겠지 ..?