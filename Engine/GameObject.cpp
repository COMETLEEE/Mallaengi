#include "pch.h"
#include <algorithm>
#include "GameObject.h"

// 트랜스폼은 당연히 가지고 있어야지 ..!
GameObject::GameObject() :
	mTransform(new Transform(this)),
	mCollision(nullptr),
	mRenderer(nullptr),
	mAnimator(nullptr),
	mCamera(nullptr),
	mReservedGameObject(nullptr),
	mTime(0),
	mID(0)
{

}

GameObject::~GameObject()
{
	if (mTransform != nullptr)
		delete mTransform;

	if (mCollision != nullptr)
		delete mCollision;

	if (mAnimator != nullptr)
		delete mAnimator;

	if (mRenderer != nullptr)
	{
		mRenderer->Release();
		delete mRenderer;
	}

	if (mCamera != nullptr)
		delete mCamera;
}

void GameObject::FixedUpdate()
{
}

void GameObject::Update()
{
	// 여기서 컴포넌트들의 Update를 진행하면 될 것 같다 ..
	if (mAnimator != nullptr)
		mAnimator->Play();

	if (mCamera != nullptr)
		mCamera->UpdateCamera();
}

void GameObject::LateUpdate()
{
}

CircleCollision* GameObject::AddCircleCollision()
{
	if (mCollision != nullptr)
		return dynamic_cast<CircleCollision*>(mCollision);

	CircleCollision* circleCollision = new CircleCollision(this);

	mCollision = circleCollision;

	return circleCollision;
}

AABBCollision* GameObject::AddAABBCollision()
{
	if (mCollision != nullptr)
		return dynamic_cast<AABBCollision*>(mCollision);

	AABBCollision* aabbCollision = new AABBCollision(this);

	mCollision = aabbCollision;

	return aabbCollision;
}

RectRenderer* GameObject::AddRectRenderer()
{
	if (mRenderer != nullptr)
		return dynamic_cast<RectRenderer*>(mRenderer);

	RectRenderer* rectRenderer = new RectRenderer(this);

	mRenderer = rectRenderer;

	return rectRenderer;
}

SpriteRenderer* GameObject::AddSpriteRenderer()
{
	if (mRenderer != nullptr)
		return dynamic_cast<SpriteRenderer*>(mRenderer);

	SpriteRenderer* spriteRenderer = new SpriteRenderer(this);

	mRenderer = spriteRenderer;

	return spriteRenderer;
}