#include "PreCompiledHeader.h"
#include "IntroBackGround.h"

#include "Player.h"

#define INTRO_SCROLL_X_SPEED 0.1f
#define INTRO_SCROLL_Y_SPEED 0.01f

IntroBackGround::IntroBackGround()
{
	SetTag("BackGround");

	AddSpriteRenderer()->SetSortOrder(10);

	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	GetTransform()->SetPosition(Vector2D(size.width / 2, size.height / 2 - 300.f));
}

IntroBackGround::~IntroBackGround()
{
}

void IntroBackGround::LateUpdate()
{
	GameObject::LateUpdate();

	// Intro Scene에서 배경을 이동시키지 않아서 전체 주석

	//// 플레이어의 위치를 메이플 스토리처럼 따라올 수 있도록
	//Vector2D playerPos = Game::GetInstance().GetPlayer()->GetTransform()->GetPosition();

	//D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	//// 약간 이런 식으로 계산하면 적당하게 메이플처럼 스크롤되는 느낌으로 할 수 있지 않을까 ..?
	//GetTransform()->SetPosition(Vector2D(size.width / 2 - 70.f - size.width / 2 * INTRO_SCROLL_X_SPEED, size.height / 2 - 300.f - size.height / 2 * INTRO_SCROLL_Y_SPEED));
}