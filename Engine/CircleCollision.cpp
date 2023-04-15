#include "pch.h"
#include "CircleCollision.h"
#include "Transform.h"
#include "GameObject.h"

CircleCollision::CircleCollision(GameObject* object) :
	Collision(object)
{
	mRadius = 10.0f;
}

CircleCollision::~CircleCollision()
{

}

bool CircleCollision::CheckCollision(Collision* collision)
{
	// 본인
	Transform* transform = this->GetGameObject()->GetTransform();

	// 다른 녀석
	Transform* otherTransform = collision->GetGameObject()->GetTransform();

	// 어떤 Collision 인지 체크
	CircleCollision* isCircle = dynamic_cast<CircleCollision*>(collision);

	// 체크한 Collision이 있을 때!
	if (isCircle != nullptr)
	{
		// 나의 반지름+너의반지름이 < 서로의 거리보다 짧을 때
		if (this->GetRadius() + isCircle->GetRadius() < (((transform->GetPosition()) - (otherTransform->GetPosition())).GetMagnitude()))
		{
			// 충돌 안함
			return false;
		}
		else
		{
			// 충돌 함
			this->SetIsCollision(true);
			isCircle->SetIsCollision(true);

			// 충돌 시 오브젝트 정보를 남긴다.
			this->AddCollisionInfo(isCircle->GetGameObject());

			return true;
		}
	}
	return false;
}