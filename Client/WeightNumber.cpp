#include "PreCompiledHeader.h"
#include "WeightNumber.h"
#include "JsonManager.h"

WeightNumber::WeightNumber(Vector2D pos, int number)
	: mAnimClip(nullptr)
{
	if (number >= 0)
		pos.mX += 100.0f;
	else
		pos.mX -= 50.0f;

	GetTransform()->SetPosition(pos);
	GetTransform()->SetScale(Vector2D(2.5f, 2.5f));

	// 입력받은 매개변수를 통해 파일 주소를 만들고 읽어온다.
	SpriteJson spriteJson;
	char buf[16];

	_itoa_s(number, buf, 10);

	if (number == 1 || number == 3 || number == 5 || number == 10
		|| number == -1 || number == -3 || number == -5 || number == -10)
	{
		string str = "Resources\\Effects\\Weight";
		str += buf;
		str += ".json";
		spriteJson.DeserializeFromCArchive(str);

		// Json에 있는 스프라이트 정보 전부 생성
		for (int i = 0; i < spriteJson.mSpriteList.size(); i++)
		{
			SpriteInfo temp = spriteJson.mSpriteList[i];
			mSprites.push_back(new Sprite(
				temp.imageID,
				Vector2D(0.5f, 0.5f),
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
				Game::GetInstance().GetCurrentScene()->ReserveDestroy(object);
			});

		// 출력할 SpriteRenderer 객체 생성
		AddSpriteRenderer();
	}
	else
	{
		Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
	}
}

WeightNumber::~WeightNumber()
{

}

void WeightNumber::Release()
{
	GetAnimator()->Release();
}