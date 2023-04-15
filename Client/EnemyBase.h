#pragma once
#include "Player.h"


#define ENEMY_WIDTH 90.f
#define ENEMY_HEIGHT 125.f

// Character Scale Control
#define ENEMY_SCALE 1.2f

#define BLOCKING_POWER 100.f

// Box
class ItemBox;
class BoxBase;
class TransBox;

// Blocks
class BreakableBlock;

// Platforms
class Platform;
class BlockPlatform;

// 적들은 각각의 다른 상태를 가진다. (3개의 적 각각의 다른 상태)
// 추적형 투사 몬스터
enum class EnemyState
{
	Idle = 0,			// 대기
	Run = 1,			// 이동
	Die = 2,			// 사망
	Attack = 3,			// 공격
	Jump = 4,			// 점프
};

/// <summary>
/// 2022. 02. 16. MG
/// 
/// 세개의 적 FSM 만들기
/// 자유형, 추적형, 추적형 투사
/// </summary>
class EnemyBase : public GameObject
{
public:
	EnemyBase();
	~EnemyBase();

protected:
	// 이동 방향 벡터 (이동이 없다면 Zero / 이동이 있다면 Normal Vector)
	Vector2D mDirVector;

	// Update 전 위치
	Vector2D mBeforePosition;

	// 점프를 할 수 있는 상태인가 ..?
	bool mIsJumpable;

protected:
	// ---------------------------- Enemy FSM ----------------------------
	// 현재 State
	EnemyState mCurrentState;

	// 전 프레임에서의 State
	EnemyState mPrevState;

	std::vector<AnimationClip*> mAnimationClips;

	// State 트랜지션이 일어날 때 애니메이션을 알맞게 변경해주고 바뀌기
	virtual void Idle();
	virtual void Run();
	virtual void Attack();
	virtual void Jump();
	virtual void Die();

	// Enemy가 생성될 때 본인에 해당하는 애니메이션을 끼워 넣는다.
	virtual void LoadAnimationProcess();

	// 현재 상태를 체크하여 변동사항이 있을 경우 이와 관련된 이벤트를 통제합니다.
	void StateChangeProcess();

	// Hp
	int mHp;

public:
	EnemyState GetCurrentState() { return mCurrentState; }

public:
	int GetHp() { return mHp; }
	void SetHp(int value) { mHp = value; }

protected:
	// ---------------------------- Simple Physics ----------------------------
	// 초당 어느 정도의 거리를 이동하는가
	Vector2D mVelocity;

	// 중력
	float mGravity;

	// 점프력
	float mJumpPower;

	// Walk or Dash를 한다는 것은 속도의 x-value만 고민하면 되는 것 ..!
	float mMaxWalkSpeed;
	// ---------------------------- Simple Physics ----------------------------

public:
	// 물리 현상 ..
	virtual void FixedUpdate() override;

	virtual void Update() override;

	// 플레이어의 이동 방향 벡터를 반환한다.
	Vector2D GetDirVector() { return mDirVector; }

	// Velocity Getter, Setter
	Vector2D GetVelocity() { return mVelocity; }
	void SetVelocity(Vector2D value) { mVelocity = value; }

	// Block Process
	void BlockCollisionProcess(BlockBase* block);
	void BreakableBlockCollisionProcess(BreakableBlock* breakableBlock);

	// Platform Process (좌, 우, 하로는 관통 가능 / 위에서만 착지)
	void PlatformCollisionProcess(Platform* platform);
	void BlockPlatformCollisionProcess(BlockPlatform* blockplatform);

	// Box Process
	void BoxCollisionProcess(BoxBase* box);
	void TransBoxCollisionProcess(TransBox* TransBox);
	void ItemBoxCollisionProcess(ItemBox* itemBox);
};