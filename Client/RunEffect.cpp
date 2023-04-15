#include "PreCompiledHeader.h"
#include "RunEffect.h"
#include "Player.h"

RunEffect::RunEffect(GameObject* target, Vector2D direction)
	: mCharacter(target)
	, mDirection(direction)
	, mAnimClip(nullptr)
{
	// 방향에 맞춰서 반전
	GetTransform()->SetScale(Vector2D(direction.mX, 1));

	// Json파일 읽어오기
	SpriteJson spriteJson;
	spriteJson.DeserializeFromCArchive(_T("Resources\\Effects\\RunEffect.json"));

	// Json에 있는 스프라이트 정보 전부 생성
	for (int i = 0; i < spriteJson.mSpriteList.size(); i++)
	{
		SpriteInfo temp = spriteJson.mSpriteList[i];
		mSprites.push_back(new Sprite(
			temp.imageID,
			Vector2D::Zero,
			{ temp.imageRect.right - temp.imageRect.left, temp.imageRect.bottom - temp.imageRect.top },
			temp.duration,
			Vector2D(temp.imageRect.left, temp.imageRect.top),
			{ temp.pivot.mX, temp.pivot.mY }));
	}

	// 애니메이션 클립에 추가하고
	mAnimClip = new AnimationClip(mSprites);

	// 애니메이터를 생성하여 보관한다.
	AddAnimator()->SetAnimationClip(mAnimClip);

	// 애니메이터에서 애니메이션 출력이 끝나고 호출할 이벤트 함수
	GetAnimator()->SetNotLoop([](GameObject* object)
		{
			Game::GetInstance().GetPlayer()->mRunEffect = nullptr;
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(object);
		});

	// 출력할 SpriteRenderer 객체 생성
	AddSpriteRenderer();
}

RunEffect::~RunEffect()
{
	Game::GetInstance().GetPlayer()->mRunEffect = nullptr;
}

void RunEffect::Update()
{
	GameObject::Update();

	// 포지션을 항상 플레이어 쪽으로 해준다.
	GetTransform()->SetPosition(mCharacter->GetTransform()->GetPosition() - Vector2D(mDirection.mX * 37, -75));
}

void RunEffect::Release()
{
	GetAnimator()->Release();
}

void RunEffect::SetDirection(Vector2D direction)
{
	// 방향이 바뀌었을 때 사용
	mDirection = direction;
	GetTransform()->SetScale(Vector2D(direction.mX, 1));
}