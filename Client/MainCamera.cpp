#include "PreCompiledHeader.h"
#include "MainCamera.h"

#include "Player.h"

#define CAMERA_POS_PER_PLAYER 0.4f

MainCamera::MainCamera(float mapWidth, float mapHeight)
	:mPlayer(Game::GetInstance().GetPlayer())
	, mMapWidth(mapWidth)
	, mMapHeight(mapHeight)
{
	SetTag("Camera");

	AddCamera();

	GetTransform()->SetPosition(mPlayer->GetTransform()->GetPosition());

	GetTransform()->SetScale(Vector2D(CAMERA_ZOOM, CAMERA_ZOOM));

	Game::GetInstance().GetCurrentScene()->SetCamera(this);
}

MainCamera::~MainCamera()
{
}

void MainCamera::LateUpdate()
{
	GameObject::LateUpdate();

	// 이 카메라 로직은 Player를 정중앙에 두고 렌더링하는 카메라입니다.
	// 기획 의도에 따라서 코드를 작성해주어야합니다.

	Vector2D playerPos = mPlayer->GetTransform()->GetPosition();

	// 플레이어 위치가 작아지면 (점프하면) ==> 카메라 위치는 이에 비례해서 올라간다.
	float adjust = mMapHeight * CAMERA_ZOOM + (playerPos.mY - mMapHeight) * CAMERA_POS_PER_PLAYER;

	if (adjust < Graphics::GetInstance().GetScreenSize().height * CAMERA_ZOOM + 20)
		adjust = Graphics::GetInstance().GetScreenSize().height * CAMERA_ZOOM + 20;
	else if (adjust > mMapHeight - Graphics::GetInstance().GetScreenSize().height * CAMERA_ZOOM - 20)
		adjust = mMapHeight - Graphics::GetInstance().GetScreenSize().height * CAMERA_ZOOM - 20;

	if (playerPos.mX < Graphics::GetInstance().GetScreenSize().width * CAMERA_ZOOM)
		GetTransform()->SetPosition(Vector2D(Graphics::GetInstance().GetScreenSize().width * CAMERA_ZOOM, adjust));
	else if (playerPos.mX > mMapWidth - Graphics::GetInstance().GetScreenSize().width * CAMERA_ZOOM)
		GetTransform()->SetPosition(Vector2D(mMapWidth - Graphics::GetInstance().GetScreenSize().width * CAMERA_ZOOM, adjust));
	else
		GetTransform()->SetPosition(Vector2D(playerPos.mX, adjust));

	// 카메라의 첫 포지션 3105, 3105보다는 더 커질 수 없음.

	// 플레이어의 위치 기준 플레이어 위치가 줄어들 수록 카메라의 위치가 상승한다.
}

float MainCamera::GetXMovablePercent()
{
	float progress = GetTransform()->GetPosition().mX - Graphics::GetInstance().GetScreenSize().width * CAMERA_ZOOM;
	float max = mMapWidth - Graphics::GetInstance().GetScreenSize().width * CAMERA_ZOOM * 2;

	return progress / max;
}

float MainCamera::GetYMovablePercent()
{
	float progress = GetTransform()->GetPosition().mY - Graphics::GetInstance().GetScreenSize().height * CAMERA_ZOOM + 20;
	float max = mMapHeight - Graphics::GetInstance().GetScreenSize().height * CAMERA_ZOOM * 2;

	return progress / max;
}