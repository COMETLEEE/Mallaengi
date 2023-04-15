#pragma once

class FallingDum;
class EnemyBase;
class ItemBox;
// Blocks
class BlockBase;
class BreakableBlock;

// Platforms
class Platform;
class BlockPlatform;

//Box
class BoxBase;
class TransBox;

class RunEffect;
class LandingEffect;

// Simple Physics
#define MAX_FALLING_SPEED 700.f
// #define MOVE_SPEED 150.f 기존
#define MOVE_SPEED 350.f
// #define JUMP_POWER 500.f 기존
#define JUMP_POWER 1000.f
#define GRAVITY 2400.f

// 관통 플랫폼을 구현하기 위한 변수들 (이거 컨트롤할 때 무조건 플랫폼 코드 수정할 필요가 있습니다 ..)
#define ADJUST_X 15.f
// #define ADJUST_Y 15.f	// 좌, 우 충돌이 내부에서 있을 수 있으므로 Y는 조금 더 봐준다.
#define ADJUST_Y 30.f	// 좌, 우 충돌이 내부에서 있을 수 있으므로 Y는 조금 더 봐준다.
#define PLAYER_WIDTH 45.f
#define PLAYER_HEIGHT 125.f

// 박스 아래에서 충돌 후 밀려날 때 반발력 (있어야할까 ..?
#define BLOCKING_POWER 100.f

// 플레이어 단계 및 상태의 총 갯수
#define PLAYER_TOTAL_STEP 3
#define PLAYER_TOTAL_STATE 4

// Character Scale Control
#define PLAYER_SCALE 1.2f

// Trans하는데 걸리는 총 시간
#define TRANS_TIME 2.3f

// Fade In-Out Time
#define FADE_TIME 1.7f

// 말랭이 프로젝트의 주인공은 3가지의 단계를 가진다. 
enum class PlayerStep
{
	Three = 0,		// 통통이
	Two = 1,		// 보통이
	One = 2		// 말랭이
};

// 말랭이 프로젝트의 주인공은 5가지의 상태를 가진다.
enum class PlayerState
{
	Idle = 0,
	Run = 1,
	Jump = 2,
	Die = 3,
	Trans = 4		// 진화 ..!
};

// 플레이어 단계별 속도, 가속도에 영향을 미칠 변수
#define RESISTANCE 0.15f

/**
 * 말랭이 프로젝트의 주인공 클래스
 *
 * 2022. 02. 05. Comet
 */
class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	RunEffect* mRunEffect;
	LandingEffect* mLandingEffect;

private:
	// 무적 모드 !!
	bool mInvincible;

	// 플레이어의 이동 방향 벡터 (이동이 없다면 Zero / 이동이 있다면 Normal Vector)
	Vector2D mDirVector;

	// Update 전 위치
	Vector2D mBeforePosition;

	// 점프를 할 수 있는 상태인가 ..?
	bool mIsJumpable;

private:
	// ---------------------------- Player FSM ----------------------------
	// 현재 Player State
	PlayerState mCurrentState;

	// 전 프레임에서의 Player State
	PlayerState mPrevState;

	// 현재 Player Step
	PlayerStep mCurrentStep;

	// 전 프레임에서의 Player Step
	PlayerStep mPrevStep;

	// 플레이어의 목숨. 있으나 마나긴 하다.
	int mLife;

public:
	int GetPlayerLife() { return mLife; }

	// State 트랜지션이 일어날 때 애니메이션을 알맞게 변경해주고 바뀌기 ..!
	void Idle();
	void Run();
	void Jump();
	void Die();
	void Trans();

	// 죽었나요.
	bool mIsFirstDieLoop;

	// Player 단계 -> 상태별 Animation
	std::vector<std::vector<AnimationClip*>> mAnimationClips;

public:
	std::vector <std::vector<AnimationClip*>> GetAnimationClipsOfPlayer() { return mAnimationClips; }
private:

	// Player가 생성될 때 Animation Load를 담당하는 Func
	void LoadAnimationProcess();

	// 현재 상태를 체크하여 변동사항이 있을 경우 이와 관련된 이벤트를 통제합니다.
	void StateChangeProcess();
	// 몸무게를 체크하여 Step의 변동이 있을 경우 이와 관련된 이벤트를 통제합니다.
	void StepChangeProcess();

	// Hp
	int mHp;

	// 몸무게
	float mBodyWeight;

	float mPrevWeight;

public:
	PlayerStep GetPrevStep() { return mPrevStep; }
	PlayerStep GetCurrentStep() { return mCurrentStep; }

	PlayerState GetCurrentState() { return mCurrentState; }

	// 로드할 때 step을 맞춰준다. 왜냐하면 세이브된 것이 로드될 때 단계가 다를 수 있음 ..!
	void SetPlayerStep(PlayerStep step)
	{
		mCurrentStep = step;
		mPrevStep = step;
	}
	// ---------------------------- Player FSM ----------------------------
public:
	int GetHp() { return mHp; }
	void SetHp(int value) { if (mInvincible) return; mHp = value; }

	float GetBodyWeight() { return mBodyWeight; }

	void SetBodyWeight(float value) { mBodyWeight = value; if (mBodyWeight <= 60.f) mBodyWeight = 60.f; }
	void PlusBodyWeight(float delta) { mBodyWeight += delta; if (mBodyWeight <= 60.f) mBodyWeight = 60.f; }

private:
	// ---------------------------- Simple Physics ----------------------------
	// 초당 어느 정도의 거리를 이동하는가
	Vector2D mVelocity;
	
	// 중력
	float mGravity;

	// 점프력
	float mJumpPower;

	// 점프버튼을 누르고 있었던 시간
	float mJumpPressedTime;

	// 점프키가 눌렸나요 ..?
	bool mIsJumpKeyPressed;
	
	// Walk or Dash를 한다는 것은 속도의 x-value만 고민하면 되는 것 ..!
	float mMaxWalkSpeed;
	// ---------------------------- Simple Physics ----------------------------

public:
	void InitPlayer();
	// 물리 현상 ..
	virtual void FixedUpdate() override;

	virtual void Update() override;

	// 플레이어의 이동 방향 벡터를 반환한다.
	Vector2D GetDirVector() { return mDirVector; }

	void SetJumpable() { mIsJumpable = true; }
	bool GetIsJumpable() { return mIsJumpable; }

	// Velocity Getter, Setter
	Vector2D GetVelocity() { return mVelocity; }
	void SetVelocity(Vector2D value) { mVelocity = value; }

	PlayerState GetPlayerState() { return mCurrentState; }
	void SetPlayerState(PlayerState state) { mCurrentState = state; }

	// Block Process
	void BlockCollisionProcess(BlockBase* block);
	void BreakableBlockCollisionProcess(BreakableBlock* breakableBlock);

	// Platform Process (좌, 우, 하로는 관통 가능 / 위에서만 착지)
	void PlatformCollisionProcess(Platform* platform);
	void BlockPlatformCollisionProcess(BlockPlatform* blockplatform);

	// Box Process
	void BoxCollisionProcess(BoxBase* box);
	void TransBoxCollisionProcess(TransBox* transBox);
	void ItemBoxCollisionProcess(ItemBox* itemBox);

	// Enemy Process
	void EnemyCollsionProcess(EnemyBase* enemy);
	
private:
	// IntroScene에서 지켜져야하는 특별한 조건들을 담는다.
	void IntroSceneProcess();

	void StageProcess();

private:
	// 지금 해당되는 스테이지를 얼마나 플레이했나요
	float mStagePlayTime;

	// 몸무게의 변동을 위한 것
	float mAcculmulTime;

	void TimeProcess();

public:
	float GetStagePlayTime() { return mStagePlayTime; }	// UI : In-Game 시계에서 호출

	void SetStagePlayTime(float value) { mStagePlayTime = value; }	// 스테이지 별 빌드될 때 호출 (보통 0으로 만들기 위해)
};

// 1초에 어느 정도에 몸무게를 업 ..?
#define GAIN_PER_SEC 1.0f		// 10초 당 1kg