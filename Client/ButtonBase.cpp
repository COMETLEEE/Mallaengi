#include "PreCompiledHeader.h"
#include "ButtonBase.h"

#define CAMERA_ZOOM 0.7f

ButtonBase::ButtonBase() :
	mSize({ TILE_WIDTH * 2, TILE_HEIGHT }),
	mIsClicked(false),
	mIsSquare(true),			// 보통 사각형 버튼
	mIsActivated(true),
	mPivot(Vector2D(1.0f, 1.0f))
{
	// Tag를 UI로 걸러
	SetTag("UI");

	AddSpriteRenderer()->SetSortOrder(2);
}

ButtonBase::~ButtonBase()
{

}

bool ButtonBase::IsCursorOnButton()
{
	Vector2D buttonPos = GetTransform()->GetPosition();

	Vector2D mousePos = Input::GetInstance().GetCurrentMousePos();

	if (mIsSquare)
	{
		if (mPivot == Vector2D::Zero)
		{
			if (mousePos.GetX() < buttonPos.GetX() || buttonPos.GetX() + mSize.width * CAMERA_ZOOM < mousePos.GetX())
				return false;

			if (mousePos.GetY() < buttonPos.GetY() || buttonPos.GetY() + mSize.height * CAMERA_ZOOM < mousePos.GetY())
				return false;

			return true;
		}
		
		return ((buttonPos.GetX() - mSize.width * CAMERA_ZOOM / 2 < mousePos.GetX()) &&
			(mousePos.GetX() < buttonPos.GetX() + mSize.width * CAMERA_ZOOM / 2) &&
			(buttonPos.GetY() - mSize.height * CAMERA_ZOOM / 2 < mousePos.GetY()) &&
			(mousePos.GetY() < buttonPos.GetY() + mSize.height * CAMERA_ZOOM / 2)) ? true : false;
	}
	else
	{
		return buttonPos.DistanceTo(mousePos) <= mSize.width * CAMERA_ZOOM ? true : false;
	}
}

void ButtonBase::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void ButtonBase::Update()
{
	GameObject::Update();

	if ((IsCursorOnButton()) && (Input::GetInstance().GetKeyState(VK_LBUTTON) == KEYSTATE::DOWN))
		OnButtonClicked();
}

void ButtonBase::OnButtonClicked()
{
	// 이 함수를 override하여 Button이 클릭되면 실행시킬 이벤트를 구현합니다.
	//Button Click Sound
	if (SoundManager::GetInstance()->Playing(500010) != true)
		SoundManager::GetInstance()->Play(500010);
}

void ButtonBase::SetActivate(bool active)
{
	mIsActivated = active;

	if (active == true)
		GetSpriteRenderer()->SetOpacity(1.0f);
	else
		GetSpriteRenderer()->SetOpacity(0.3f);
}