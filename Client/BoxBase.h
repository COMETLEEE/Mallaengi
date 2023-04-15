#pragma once

enum class CollisionDir;
/**
 * 플레이어가 아랫면에서 치면 아이템을 생성 등 여러 이벤트를 일회성으로 실시한다.
 *
 * 2022. 02. 17. Comet
 */
class BoxBase : public GameObject
{
public:
	BoxBase();
	virtual ~BoxBase();

private:
	D2D1_SIZE_F mSize;

protected:
	// 트리거가 켜진다. (== Player가 아랫방향에서 치면 켜줌)
	bool mTrigger;
	// 트리거가 켜지고 첫 루프일 때만 이벤트를 돌리기 위함.
	bool mIsFirstLoop;

	CollisionDir mCollisionDir;

public:
	void SetCollisionDir(CollisionDir col) { mCollisionDir = col; }

	CollisionDir GetCollisionDir() { return mCollisionDir; }
	
	virtual void Update() override;

	D2D1_SIZE_F GetSize() { return mSize; }

	// 트리거를 켜준다.
	void TriggerOn() { mTrigger = true; }

	// 트리거가 되었을 때 (== Player가 아랫방향에서 쳤을 때)
	virtual void TriggerEvent();
	virtual void Release() {};
};