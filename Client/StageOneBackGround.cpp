#include "PreCompiledHeader.h"
#include "StageOneBackGround.h"

#include "Player.h"

#include "MainCamera.h"

#define SCROLL_SPEED_X 0.05f
#define SCROLL_SPEED_Y 0.01f

StageOneBackGround::StageOneBackGround()
{
	SetTag("BackGround");

	AddSpriteRenderer();

	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	GetTransform()->SetPosition(Vector2D(size.width, size.height));
}

StageOneBackGround::~StageOneBackGround()
{
	// 으어아 ..히히
}

void StageOneBackGround::LateUpdate()
{
	GameObject::LateUpdate();

	// 카메라 좌표를 가져와서 항상 배경이 출력될 수 있게 한다.
	MainCamera* camera = dynamic_cast<MainCamera*>(Game::GetInstance().GetCurrentScene()->GetCamera());
	Vector2D cameraPos = camera->GetTransform()->GetPosition();

	// 배경 크기
	D2D1_SIZE_F bgSize = GetSpriteRenderer()->GetSprite()->mSize;

	// 화면 크기
	D2D1_SIZE_F size = { Graphics::GetInstance().GetScreenSize().width / CAMERA_ZOOM, Graphics::GetInstance().GetScreenSize().height / CAMERA_ZOOM };
	
	// 화면과 배경 크기 사이의 간격
	FLOAT moreThanScreenX = bgSize.width - size.width;
	FLOAT moreThanScreenY = bgSize.height - size.height;

	if (moreThanScreenX < 0)
		moreThanScreenX = 0;

	if (moreThanScreenY < 0)
		moreThanScreenY = 0;

	// 약간 이런 식으로 계산하면 적당하게 메이플처럼 스크롤되는 느낌으로 할 수 있지 않을까 ..?
	GetTransform()->SetPosition(Vector2D(
	cameraPos.mX + moreThanScreenX * (0.5f - camera->GetXMovablePercent()), 
	cameraPos.mY + moreThanScreenY * (0.5f - camera->GetYMovablePercent())));
}