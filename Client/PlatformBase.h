#pragma once

// 충돌이 어느 방향에서 일어났는가.
enum class CollisionDir
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

/// <summary>
/// Platform One-Way Collision을 받는 오브젝트
/// 
/// 2022. 02. 09. Comet
/// </summary>
class PlatformBase : public GameObject
{
public:
	PlatformBase();
	virtual ~PlatformBase();

protected:
	D2D1_SIZE_F mSize;

	AABBCollision* mAABBCollision;

	CollisionDir mCollisionDir;

public:
	virtual void FixedUpdate() override;

	virtual void Update() override;

	D2D1_SIZE_F GetSize() { return mSize; }

	CollisionDir GetCollisionDir() { return mCollisionDir; }

	void SetCollisionDir(CollisionDir collisionDir) { mCollisionDir = collisionDir; }

	// Platform 이벤트 출력용 함수
	// virtual void OnCollisionEvent();
};