#include "PreCompiledHeader.h"
#include "FreeEnemy.h"

FreeEnemy::FreeEnemy(std::string type) :
EnemyBase(),
mDirrection(1),
mType(type),
mPauseTime(0.f),
mIsFirstLoop(true)
{
	mMoveSpeed = ENEMY_MOVE_SPEED;

	std::random_device rd;

	mMt = std::mt19937(rd());

	mPauseDist = std::uniform_int_distribution<int>(1, 3);

	mDistanceDist = std::uniform_int_distribution<int>(70.f, 150.f);

	mAnimationClips = std::vector<AnimationClip*>(3);

	LoadAnimationProcess();

	if (mType == "Hamburger")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_IDLE"));
	else if (mType == "SandBag")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_IDLE"));
	else if (mType == "Dum")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_IDLE"));
	else if (mType == "NiddleDown")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN"));
	else if (mType == "Down")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN"));
	else if (mType == "Face")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_IDLE"));
	else if (mType == "Fur")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_IDLE"));
}

FreeEnemy::FreeEnemy(std::string type, bool IsUpper):
	EnemyBase(),
	mDirrection(1),
	mType(type),
	mPauseTime(0.f),
	mIsFirstLoop(true),
mIsUpper(IsUpper)
{
	std::random_device rd;

	mMt = std::mt19937(rd());

	mPauseDist = std::uniform_int_distribution<int>(1, 4);

	mDistanceDist = std::uniform_int_distribution<int>(300, 600);

	mAnimationClips = std::vector<AnimationClip*>(3);

	LoadAnimationProcess();

	mMoveSpeed = ENEMY_MOVE_SPEED;

	if (mType == "Hamburger")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_IDLE"));
	else if (mType == "SandBag")
	{
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_IDLE"));
	}
	else if (mType == "Dum")
	{
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_IDLE"));
	}
	else if (mType == "NiddleDown")
	{
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN"));
	}
	else if (mType == "Down")
	{
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN"));
	}
	else if (mType == "Face")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_IDLE"));
	else if (mType == "Fur")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_IDLE"));
}

FreeEnemy::FreeEnemy(std::string type, int IsFalling, float MoveSpeed) :
	FreeEnemy(type)
{
	mIsFalling = IsFalling;

	mMoveSpeed = MoveSpeed;

	if (mIsFalling == -1)
		mTransform->SetScale(Vector2D(-ENEMY_SCALE, ENEMY_SCALE));
}

FreeEnemy::~FreeEnemy()
{
}

void FreeEnemy::LoadAnimationProcess()
{
	// 각각의 타입에 맞는 Animation을 재생한다.
	if (mType == "Hamburger")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_DIE");
	}
	else if (mType == "SandBag")
	{
		// 샌드백 ^^
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_DIE");
	}
	else if (mType == "Dum")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_DIE");
	}
	else if (mType == "NiddleDown")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN");
	}
	else if (mType == "Down")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN");
	}
	else if (mType == "Face")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_DIE");
	}
	else if (mType == "Fur")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_DIE");
	}
}

void FreeEnemy::Idle()
{
	if (mIsFirstLoop)
	{
		// 랜덤 대기 시간을 생성한다.
		mPauseTime = static_cast<float>(mPauseDist(mMt));

		if ((mIsUpper))
			mPauseTime = 0.f;
		else if (mIsFalling == -1)
			mPauseTime = 0.7f;

		mIsFirstLoop = false;
	}
	else
	{
		mPauseTime -= Timer::GetInstance().GetDeltaTime() / 1000.f;

		if (mPauseTime <= 0)
		{
			mDirrection *= -1;

			if ((mIsUpper) || (mIsFalling == -1))
				mDirrection = -1;

			mTransform->SetScale(Vector2D(static_cast<float>(mDirrection) * ENEMY_SCALE, ENEMY_SCALE));

			mCurrentState = EnemyState::Run;

			mIsFirstLoop = true;
		}
	}
}

void FreeEnemy::Run()
{
	if (mIsFirstLoop)
	{
		mDistance = mDistanceDist(mMt);

		if ((mIsUpper) || (mIsFalling == -1))
			mDistance = 3000.f;

		mIsFirstLoop = false;
	}
	else
	{
		mVelocity.mX = mDirrection * mMoveSpeed;

		mDistance -= mMoveSpeed * Timer::GetInstance().GetDeltaTime() / 1000.f;

		if (mDistance <= 0)
		{
			mCurrentState = EnemyState::Idle;

			mIsFirstLoop = true;
		}
	}
}

void FreeEnemy::Die()
{
	// Time을 새면서 투명해지자 ..
	GetSpriteRenderer()->SetOpacity(GetSpriteRenderer()->GetOpacity() - 0.017f);

	if (GetSpriteRenderer()->GetOpacity() <= 0.f)
		Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
}