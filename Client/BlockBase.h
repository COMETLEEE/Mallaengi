#pragma once

enum class CollisionDir;

/// <summary>
/// 모든 블록들의 기본이 되는 클래스
/// 
/// 2022. 02. 07. Comet
/// </summary>
class BlockBase : public GameObject
{
public:
	BlockBase();
	virtual ~BlockBase();

protected:
	// 가로, 세로 (타일 맵 크기 받아서 하면 될듯 ..?)
	// 렌더러, 콜리젼 모두 사이즈 맞춰 주어야 한다.
	D2D1_SIZE_F mSize;

	CollisionDir mCollisionDir;

	// 이걸 갖고 있도록 하자. 어차피 계속 이걸 쓸거니까.
	AABBCollision* mAABBCollision;

public:
	void SetCollisionDir(CollisionDir col) { mCollisionDir = col; }
	
	CollisionDir GetCollisionDir() { return mCollisionDir; }

	virtual void FixedUpdate() override;

	virtual void Update() override;

	D2D1_SIZE_F GetSize() { return mSize; }

	// 이 친구를 오버라이드해서, 필요한 상황에 부른다.
	//virtual void OnCollisionEvent();
};