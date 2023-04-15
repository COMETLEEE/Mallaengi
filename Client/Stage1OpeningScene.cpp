#include "PreCompiledHeader.h"
#include "Stage1OpeningScene.h"

#include "SubCamera.h"
#include "NarrativeSprite.h"

#include "JsonManager.h"

/// <summary>
/// 씬에 효과음 넣는 테스트 클래스
/// 안쓴다면 지우거나 사용시에 참고하여 사용
/// 
/// 2022. 02. 24 JK
/// </summary>
class testobject : public GameObject
{
	float volume;	// 효과음 볼륨
	float delay;	// 출력까지 지연 시간

public:
	testobject(float _delay) : volume(1.0f), delay(_delay) {};

	virtual void Update() override
	{
		// 지연 시간동안 대기
		if (delay <= 0.0f)
		{
			// 출력 후 삭제
			SoundManager::GetInstance()->Play(500032);
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
		}
		else
		{
			delay -= Timer::GetInstance().GetDeltaTime() / 1000;
		}
	}
};

Stage1OpeningScene::Stage1OpeningScene()
	: Scene("StageOneOpening")
{

}

Stage1OpeningScene::~Stage1OpeningScene()
{

}

void Stage1OpeningScene::BuildScene()
{
	Scene::BuildScene();

	AddGameObject(new SubCamera());

	// Opening Narrative 데이터 읽어오기
	NarrativeJson narrativeJson;
	narrativeJson.DeserializeFromFile("Resources\\Json\\Stage1OpeningNarrativeTable.json");

	for (int i = 0; i < narrativeJson.mNarrativeList.size(); i++)
	{
		const NarrativeData& data = narrativeJson.mNarrativeList[i];

		// 스프라이트 데이터 세팅
		Sprite* sprite = new Sprite(
			data.imageID,	// Image ID
			Vector2D::Zero,	// Pivot
			{ data.imageSize.width / CAMERA_ZOOM, data.imageSize.height / CAMERA_ZOOM }, // Size
			0.0f,			// Delay
			Vector2D::Zero);// Sheet Position

		// 스프라이트와 출력 지연, 지속, 속도 등 인자로 넣어주고 좌표 설정
		NarrativeSprite* narrativeSprite = new NarrativeSprite(sprite, data.delay, data.duration, data.alphaSpeed);
		narrativeSprite->GetTransform()->SetPosition({ data.imagePos.mX / CAMERA_ZOOM, data.imagePos.mY / CAMERA_ZOOM });

		// 씬에 오브젝트 추가
		AddGameObject(narrativeSprite);
	}

	// 씬에 효과음을 넣는다면 이런식으로..
	AddGameObject(new testobject(34));
	
	// Story_1
	SoundManager::GetInstance()->Play(500005);
}