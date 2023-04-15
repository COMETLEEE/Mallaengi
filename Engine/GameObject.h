#pragma once
#include <string>
#include "AABBCollision.h"
#include "CircleCollision.h"
#include "Renderer.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "RectRenderer.h"
#include "Camera.h"
#include "Timer.h"

class Transform;

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 게임 내의 모든 오브젝트를 관리하기 위한 클래스
/// </summary>
class GameObject
{
	// 필요한거
public:
	GameObject();
	virtual ~GameObject();

	// 만약 물리 현상이 있다면, 여기서 처리하겠습니다.
	virtual void FixedUpdate();

	// 여기서 컴포넌트들의 Update를 진행하고
	// 상속받은 객체들의 Update (Script 개념)는 따로 Override 후 진행할 계획입니다.
	virtual void Update();

	// 가장 마지막에 Update 되어야하는 친구들 (E.x. Camera)
	virtual void LateUpdate();

	virtual void Release() {}

protected:
	// 추가될 때마다 소멸자에다 delete 추가하는 것 잊지마 ..!
	// Getter / Adder 추가하는 것도 ..!
	Transform* mTransform;

	Collision* mCollision;

	Renderer* mRenderer;

	Animator* mAnimator;

	Camera* mCamera;

	GameObject* mReservedGameObject;							// 예약생성을 위해 오브젝트의 정보를 잠시 저장할 변수

	double mTime;

	std::string mTag;											// 오브젝트들의 분류를 위한 변수

	unsigned int mID;											// 타일 ID

public:
	Transform* GetTransform() { return mTransform; }

	Collision* GetCollision() { return mCollision; }
	AABBCollision* GetAABBCollision() { return dynamic_cast<AABBCollision*>(mCollision); }
	CircleCollision* AddCircleCollision();
	AABBCollision* AddAABBCollision();

	Renderer* GetRenderer() { return mRenderer; }
	RectRenderer* AddRectRenderer();
	SpriteRenderer* AddSpriteRenderer();
	SpriteRenderer* GetSpriteRenderer() { return dynamic_cast<SpriteRenderer*>(mRenderer); }

	Animator* GetAnimator() { return mAnimator; }
	Animator* AddAnimator() { mAnimator = new Animator(this); return mAnimator; }

	Camera* GetCamera() { return mCamera; }
	Camera* AddCamera() { mCamera = new Camera(this); Graphics::GetInstance().SetCamera(mCamera); return mCamera; }

	std::string GetTag() { return mTag; }
	void SetTag(std::string tag) { mTag = tag; }
	void SetID(unsigned int ID) { mID = ID; }
	unsigned int GetID() { return mID; }
};

// 게임 오브젝트 삭제하는 방법

// 예약 형식 (다음 프레임을 시잘할 때 삭제가 예약된 친구들을 다 삭제하고 프레임 업데이트에 들어간다.)

// 삭제를 예약한다는 것은 그 친구의 뭔가 플래그 (mReservedDestroy 켜준다거나 등등 ..)

// 그럼 내가 업데이트할때마다 체크해서 삭제하면 그만이야. 아주 쉽죠 ?


// 1. 삭제를 예약하는 기능

// 2. 생성을 예약하는 기능


// 원과 박스의 충돌감지