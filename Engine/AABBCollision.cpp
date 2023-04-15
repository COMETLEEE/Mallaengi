#include "pch.h"
#include "AABBCollision.h"
#include "Transform.h"
#include "GameObject.h"


// 타일 크기에 맞게 사이즈를 바꿀 필요가 있습니다.
AABBCollision::AABBCollision(GameObject* object) :
	Collision(object)
{
	// 타일 크기에 맞게 맞춰두었습니다.
	mSize.width = 80.f;
	mSize.height = 77.f;
}

AABBCollision::~AABBCollision()
{

}

bool AABBCollision::CheckCollision(Collision* collision)
{
	// 본인
	Transform* transform = this->GetGameObject()->GetTransform();

	Vector2D scale = transform->GetScale();

	// 다른 녀석
	Transform* otherTransform = collision->GetGameObject()->GetTransform();

	Vector2D otherScale = otherTransform->GetScale();

	// 어떤 Collision 인지 체크
	AABBCollision* isAABB = dynamic_cast<AABBCollision*>(collision);

	// 원과 박스를 체크 할 때
	CircleCollision* isCircle = dynamic_cast<CircleCollision*>(collision);

	// 박스와 박스의 충돌감지
	if (isAABB != nullptr)
	{
		/// 너와 나의 위치보다 각자의 반길이를 더한 값이 더 클때 충돌!
		if (abs(transform->GetPosition().GetX() - otherTransform->GetPosition().GetX()) <
			((this->mSize.width / 2) * abs(scale.mX)) + ((isAABB->mSize.width / 2) * abs(otherScale.mX)) &&
			abs(transform->GetPosition().GetY() - otherTransform->GetPosition().GetY()) <
			((this->mSize.height / 2) * abs(scale.mY)) + ((isAABB->mSize.height / 2) * abs(otherScale.mY)))
		{
			this->SetIsCollision(true);
			isAABB->SetIsCollision(true);

			AddCollisionInfo(isAABB->GetGameObject());				// 오브젝트의 충돌 정보 저장
			isAABB->AddCollisionInfo(this->GetGameObject());

			return true;
		}
		else
			return false;
	}
	// 원과 박스의 충돌 감지
	else if (isCircle != nullptr)
	{
		// 박스, 원 충돌 시 크기가 늘어난 사각형을 위한 rect
		D2D_RECT_F rect = { transform->GetPosition().GetX() - (this->mSize.width / 2),
							transform->GetPosition().GetY() - (this->mSize.height / 2),
							transform->GetPosition().GetX() + (this->mSize.width / 2),
							transform->GetPosition().GetY() + (this->mSize.height / 2)
		};

		// 원의 좌표와 반지름
		float centerX = static_cast<int>(isCircle->GetGameObject()->GetTransform()->GetPosition().GetX());
		float centerY = static_cast<int>(isCircle->GetGameObject()->GetTransform()->GetPosition().GetY());
		float radius = static_cast<int>(isCircle->GetRadius());

		// 원의 좌표와 사각형의 꼭짓점들을 비교
		if ((rect.left <= centerX && centerX <= rect.right) || (rect.top <= centerY && centerY <= rect.bottom))
		{
			// 사각형의 좌 우 상 하로 원의 반지름만큼 크기를 늘린 사각형 안에 원의 중심이 들어오는가? -> 충돌이다!
			if (
				((rect.left - isCircle->GetRadius()) <= centerX &&		// 좌
				centerX <= (rect.right + isCircle->GetRadius())) &&		// 우
				((rect.top - isCircle->GetRadius()) <= centerY &&		// 상
				centerY <= (rect.bottom + isCircle->GetRadius()))		// 하
				)
			{
				this->SetIsCollision(true);
				isCircle->SetIsCollision(true);

				this->AddCollisionInfo(this->GetGameObject());
				isCircle->AddCollisionInfo(isCircle->GetGameObject());

				return true;
			}
		}

		// 원의 중심좌표
		Vector2D centerOfCircle = Vector2D(centerX, centerY);

		// 사각형 모서리 4개의 점이 원 안에 있는지 체크 -> 원의 반지름보다 사각형의 각 꼭짓점의 거리가 작으면? 충돌이다 !
		if ((Vector2D(rect.left, rect.top).DistanceTo(centerOfCircle) <= radius) ||
			(Vector2D(rect.right, rect.top).DistanceTo(centerOfCircle) <= radius) ||
			(Vector2D(rect.left, rect.bottom).DistanceTo(centerOfCircle) <= radius) ||
			(Vector2D(rect.right, rect.bottom).DistanceTo(centerOfCircle) <= radius))
		{
			this->SetIsCollision(true);
			isCircle->SetIsCollision(true);

			this->AddCollisionInfo(this->GetGameObject());		
			isCircle->AddCollisionInfo(isCircle->GetGameObject());

			return true;
		}
	}

	return false;
}