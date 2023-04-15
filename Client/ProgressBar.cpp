#include "PreCompiledHeader.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(Sprite* sprite, bool isFront, void (*func)(float Percent), float percent)
	: mValue(percent)
	, mMax(1.0f)
	, mFront(isFront)
	, mFunc(func)
{
	// 스프라이트를 복사생성한다.
	GetSpriteRenderer()->SetSprite(new Sprite(*sprite));

	// 스프라이트의 원래 사이즈를 저장
	mSize = GetSpriteRenderer()->GetSprite()->mSize;

	// 진행바니까 왼쪽에서부터 출력해야 관리하기 편한거 같다.
	mPivot = Vector2D::Zero;
	GetTransform()->SetPosition(GetTransform()->GetPosition() - Vector2D(mSize.width * CAMERA_ZOOM / 2, 0));
}

ProgressBar::~ProgressBar()
{
	delete GetSpriteRenderer()->GetSprite();
}

void ProgressBar::Update()
{
	ButtonBase::Update();

	// Bar가 클릭됐을 때 마우스 좌표에 따라 값을 변화시켜준다.
	if (mIsClicked == true)
	{
		Vector2D pos = GetTransform()->GetPosition();

		Vector2D mousePos = Input::GetInstance().GetCurrentMousePos();

		SetPercent((mousePos.mX - pos.mX) / mSize.width / CAMERA_ZOOM);

		mFunc(mValue / mMax);
	}

	// 마우스를 때면 false
	if (Input::GetInstance().GetKeyState(VK_LBUTTON) == KEYSTATE::UP)
		mIsClicked = false;
}

void ProgressBar::SetPercent(float percent)
{
	// 퍼센트를 0 ~ 1사이로 고정시킨다.
	if (percent < 0.0f)
		mValue = 0.0f;
	else if (percent > 1.0f)
		mValue = mMax;
	else
		mValue = percent * mMax;

	// 변경된 값을 스프라이트에 적용
	GetSpriteRenderer()->GetSprite()->mSize.width = mSize.width * mValue / mMax;
}

void ProgressBar::SetIncrease(float rate)
{
	mValue += 0.01 * rate;

	if (mValue > mMax)
		mValue = mMax;

	GetSpriteRenderer()->GetSprite()->mSize.width = mSize.width * mValue / mMax;
}

void ProgressBar::SetDecrease(float rate)
{
	mValue -= 0.01 * rate;

	if (mValue < 0.0f)
		mValue = 0.0f;

	GetSpriteRenderer()->GetSprite()->mSize.width = mSize.width * mValue / mMax;
}

void ProgressBar::OnButtonClicked()
{
	if (mIsActivated != true)
		return;

	ButtonBase::OnButtonClicked();

	if (mFront == true)
	{
		mIsClicked = true;
	}
}