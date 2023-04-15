#include "pch.h"
#include "Camera.h"

Camera::Camera(GameObject* gameObject)
	: mGameObject(gameObject), 
	mSize(Graphics::GetInstance().GetScreenSize()),
	mLeftTop(Vector2D::Zero)
{
}

Camera::~Camera()
{

}

void Camera::UpdateCamera()
{
	// 화면 사이즈 받아오기
	mSize = Graphics::GetInstance().GetScreenSize();

	// 오브젝트를 중심에 두고 움직임에 따라 다니는 카메라
	Transform* transform = mGameObject->GetTransform();

	// 카메라의 pos에 월드좌표값 넣기? 타입 다름
	Vector2D cameraPos = transform->GetPosition();

	// 카메라의 좌상단 -> 화면 전체의 중앙값 -> 캐릭터의 중앙으로 잡아야 함
	Vector2D leftTop = cameraPos - Vector2D(mSize.width / 2, mSize.height / 2);

	// 카메라의 좌상단에 값 대입
	mLeftTop = leftTop;
}