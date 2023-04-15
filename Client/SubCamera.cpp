#include "PreCompiledHeader.h"
#include "SubCamera.h"

SubCamera::SubCamera()
{
	SetTag("Camera");

	AddCamera();

	D2D1_SIZE_F size = GetCamera()->GetSize();
	  
	// SubCamera는 고정이다 ..!
	GetTransform()->SetPosition(Vector2D(size.width / 2 / CAMERA_ZOOM, size.height / 2 / CAMERA_ZOOM));
	// 카메라 줌.
	GetTransform()->SetScale(Vector2D(CAMERA_ZOOM, CAMERA_ZOOM));

	Game::GetInstance().GetCurrentScene()->SetCamera(this);
}

SubCamera::~SubCamera()
{

}

void SubCamera::LateUpdate()
{
	GameObject::LateUpdate();

	// 딱히 업데이트할 필요가 없습니다. 정중앙에 고정되는 카메라니까 ..!
}