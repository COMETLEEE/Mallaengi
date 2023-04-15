#include "PreCompiledHeader.h"
#include "Resource.h"

// JsonFile을 다루기 위한 친구
#include "JsonManager.h"

// 로드하는 스프라이트가 늘어나면 Initialize의 순서 변경이 없는 한
// 이 밑으로 1씩 더하면서 추가해주시면 됩니다. (이 인덱스는 엔진 내부 컬렉션에서 불러올 때 사용하는 인덱스입니다.)
// 주말에 제이슨으로 정리한다. 무슨일이 있어도. (실패 .. 사유: 엑셀이 집 노트북으로 안됨 .. 망함 ..)
enum SpriteIndex
{
	// 플레이어 3단계
	PLAYER_THREE_IDLE = 0,
	PLAYER_THREE_RUN = 1,
	PLAYER_THREE_JUMP = 2,
	PLAYER_THREE_DIE = 3,

	// 플레이어 2단계
	PLAYER_TWO_IDLE = 4,
	PLAYER_TWO_RUN = 5,
	PLAYER_TWO_JUMP = 6,
	PLAYER_TWO_DIE = 7,

	// 플레이어 1단계
	PLAYER_ONE_IDLE = 8,
	PLAYER_ONE_RUN = 9,
	PLAYER_ONE_JUMP = 10,
	PLAYER_ONE_DIE = 11,

	// Intro
	INTRO_LOGO = 12,
	INTRO_START = 13,
	INTRO_START2 = 14,
	INTRO_INFO = 15,
	INTRO_TUTO = 16,
	INTRO_EXIT = 17,
	INTRO_COPY = 18,

	// Fade In / Out
	FADE_INOUT = 19,

	// STAGE 1 (Example, Test)
	STAGE_1_BACKGROUND = 20,

	// PLAYER_WEIGHT_CHANGE
	THREE_TO_TWO = 21,
	TWO_TO_THREE = 22,
	TWO_TO_ONE = 23,
	ONE_TO_TWO = 24,

	// DIE SCENE
	DIE_FACE = 25,
	DIE_RESTART = 26,
	DIE_NUMBERS = 27,

	// OPTION
	OPTION_MENU = 28,
	OPTION_BACK_PROGRESS_BAR = 29,
	OPTION_FRONT_PROGRESS_BAR = 30,
	OPTION_PROGRESS_BAR = 31,
	OPTION_BGMText = 32,
	OPTION_SFXText = 33,
	OPTION_RESTART = 34,
	OPTION_BACK = 35,
	OPTION_TITLE = 36,
	OPTION_EXIT = 37,

	// UI_BODYSCALE
	UI_BODYSCALE = 38,
	UI_SCALENUMBER = 39,

	// ENEMY_BURGER
	ENEMY_BURGER_IDLE = 40,
	ENEMY_BURGER_RUN = 41,
	ENEMY_BURGER_ATTACK = 42,
	ENEMY_BURGER_DIE = 43,

	// BIRD_TRAP
	BIRD_GRAY_IDLE = 44,
	BIRD_GRAY_RUN = 45,
	BIRD_BLACK_IDLE = 46,
	BIRD_BLACK_RUN = 47,

	// STAGE 2
	STAGE_2_BACKGROUND = 48,
	NACHO_SHURIKEN = 49,

	// ENEMY_SANDBAG
	ENEMY_SANDBAG_IDLE = 50,
	ENEMY_SANDBAG_RUN = 51,
	ENEMY_SANDBAG_ATTACK = 52,
	ENEMY_SANDBAG_DIE = 53,

	// ENEMY_DUM
	ENEMY_DUM_IDLE = 54,
	ENEMY_DUM_RUN = 55,
	ENEMY_DUM_DIE = 56,

	// CAT_BOX
	TRAP_CAT_SETUP = 57,
	TRAP_CAT_ATTACK = 58,

	// 덤벨 굴러간다
	TRAP_NIDDLE_DUM_DOWN = 59,
	TRAP_DUM_DOWN = 60,

	// WATCH_INGAME
	WATCH_COLON = 61,
	WATCH_NUMBERS = 62,

	// STAGE 3
	STAGE_3_BACKGROUND = 63,

	// FACE
	ENEMY_FACE_IDLE = 64,
	ENEMY_FACE_RUN = 65,
	ENEMY_FACE_DIE = 66,

	// FUR
	ENEMY_FUR_IDLE = 67,
	ENEMY_FUR_RUN = 68,
	ENEMY_FUR_DIE = 69,

	// Face
	LIFE_FACE = 70
};

Resource::Resource()
{
}

Resource::~Resource()
{
	// 모든 리소스들 빠이하면 됩니다 ..!
	for (auto iter = mAllAnimationClips.begin(); iter != mAllAnimationClips.end(); iter++)
		delete iter->second;

	for (auto iter = mAllSprites.begin(); iter != mAllSprites.end(); iter++)
	{
		delete iter->second;
	}
}

// 다음 프로젝트때는 무슨 일이 있어도 데이터 시트 쓴다. 처음부터 끝까지
void Resource::Initialize()
{
#pragma region 통통이
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/3.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/3.png");
	// Jump Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Jump/3.png");
	// Die Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Die/3.png");

#pragma region Idle
	Sprite* idle1 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(0.f, 30.f));
	Sprite* idle2 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(100.f, 30.f));
	Sprite* idle3 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(200.f, 30.f));
	Sprite* idle4 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(300.f, 30.f));
	Sprite* idle5 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(400.f, 30.f));
	Sprite* idle6 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(500.f, 30.f));
	Sprite* idle7 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(600.f, 30.f));
	Sprite* idle8 = new Sprite(PLAYER_THREE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(700.f, 30.f));

	std::vector<Sprite*> idle;

	idle.push_back(idle1);
	idle.push_back(idle2);
	idle.push_back(idle3);
	idle.push_back(idle4);
	idle.push_back(idle5);
	idle.push_back(idle6);
	idle.push_back(idle7);
	idle.push_back(idle8);

	AnimationClip* idleAnim = new AnimationClip(idle);
	
	mAllAnimationClips.emplace("PLAYER_THREE_IDLE", idleAnim);
#pragma endregion

#pragma region Run
	Sprite* run1 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(0.f, 30.f));
	Sprite* run2 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(100.f, 30.f));
	Sprite* run3 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(200.f, 30.f));
	Sprite* run4 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(300.f, 30.f));
	Sprite* run5 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(400.f, 30.f));
	Sprite* run6 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(500.f, 30.f));
	Sprite* run7 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(600.f, 30.f));
	Sprite* run8 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(700.f, 30.f));
	Sprite* run9 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(800.f, 30.f));
	Sprite* run10 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(900.f, 30.f));
	Sprite* run11 = new Sprite(PLAYER_THREE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(1000.f, 30.f));

	std::vector<Sprite*> run;

	run.push_back(run1);
	run.push_back(run2);
	run.push_back(run3);
	run.push_back(run4);
	run.push_back(run5);
	run.push_back(run6);
	run.push_back(run7);
	run.push_back(run8);
	run.push_back(run9);
	run.push_back(run10);
	run.push_back(run11);

	AnimationClip* runAnim = new AnimationClip(run);

	mAllAnimationClips.emplace("PLAYER_THREE_RUN", runAnim);
#pragma endregion

#pragma region Jump
	Sprite* jump1 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(0.f, 30.f));
	Sprite* jump2 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(100.f, 23.f));
	Sprite* jump3 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 1.0f, Vector2D(200.f, 18.f));
	Sprite* jump4 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(300.f, 18.f));
	Sprite* jump5 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(400.f, 27.f));
	Sprite* jump6 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(500.f, 30.f));
	Sprite* jump7 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(600.f, 30.f));
	Sprite* jump8 = new Sprite(PLAYER_THREE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 10.0f, Vector2D(700.f, 30.f));

	std::vector<Sprite*> jump;

	jump.push_back(jump1);
	jump.push_back(jump2);
	jump.push_back(jump3);
	jump.push_back(jump4);
	jump.push_back(jump5);
	jump.push_back(jump6);
	jump.push_back(jump7);
	jump.push_back(jump8);

	AnimationClip* jumpAnim = new AnimationClip(jump);

	mAllAnimationClips.emplace("PLAYER_THREE_JUMP", jumpAnim);
#pragma endregion

#pragma region Die
	Sprite* die1 = new Sprite(PLAYER_THREE_DIE, Vector2D(0.5f, 0.5f), { 100, 125 }, 10.f, Vector2D(0.f, 30.f));

	std::vector<Sprite*> die;

	die.push_back(die1);

	AnimationClip* dieAnim = new AnimationClip(die);
	mAllAnimationClips.emplace("PLAYER_THREE_DIE", dieAnim);
#pragma endregion
#pragma endregion

#pragma region 보통이
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/2.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/2.png");
	// Jump Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Jump/2.png");
	// Die Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Die/2.png");

#pragma region Idle
	Sprite* idleTwo1 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(0.f, 30.f));
	Sprite* idleTwo2 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(100.f, 30.f));
	Sprite* idleTwo3 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(200.f, 30.f));
	Sprite* idleTwo4 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(300.f, 30.f));
	Sprite* idleTwo5 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(400.f, 30.f));
	Sprite* idleTwo6 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(500.f, 30.f));
	Sprite* idleTwo7 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(600.f, 30.f));
	Sprite* idleTwo8 = new Sprite(PLAYER_TWO_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(700.f, 30.f));

	std::vector<Sprite*> idleTwo;

	idleTwo.push_back(idleTwo1);
	idleTwo.push_back(idleTwo2);
	idleTwo.push_back(idleTwo3);
	idleTwo.push_back(idleTwo4);
	idleTwo.push_back(idleTwo5);
	idleTwo.push_back(idleTwo6);
	idleTwo.push_back(idleTwo7);
	idleTwo.push_back(idleTwo8);

	AnimationClip* idleTwoAnim = new AnimationClip(idleTwo);
	mAllAnimationClips.emplace("PLAYER_TWO_IDLE", idleTwoAnim);
#pragma endregion

#pragma region Run
	Sprite* runTwo1 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(0.f, 30.f));
	Sprite* runTwo2 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(100.f, 30.f));
	Sprite* runTwo3 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(200.f, 30.f));
	Sprite* runTwo4 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(300.f, 30.f));
	Sprite* runTwo5 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(400.f, 30.f));
	Sprite* runTwo6 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(500.f, 30.f));
	Sprite* runTwo7 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(600.f, 30.f));
	Sprite* runTwo8 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(700.f, 30.f));
	Sprite* runTwo9 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(800.f, 30.f));
	Sprite* runTwo10 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(900.f, 30.f));
	Sprite* runTwo11 = new Sprite(PLAYER_TWO_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(1000.f, 30.f));

	std::vector<Sprite*> runTwo;

	runTwo.push_back(runTwo1);
	runTwo.push_back(runTwo2);
	runTwo.push_back(runTwo3);
	runTwo.push_back(runTwo4);
	runTwo.push_back(runTwo5);
	runTwo.push_back(runTwo6);
	runTwo.push_back(runTwo7);
	runTwo.push_back(runTwo8);
	runTwo.push_back(runTwo9);
	runTwo.push_back(runTwo10);
	runTwo.push_back(runTwo11);

	AnimationClip* runTwoAnim = new AnimationClip(runTwo);
	mAllAnimationClips.emplace("PLAYER_TWO_RUN", runTwoAnim);
#pragma endregion

#pragma region Jump
	Sprite* jumpTwo1 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(0.f, 30.f));
	Sprite* jumpTwo2 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(100.f, 23.f));
	Sprite* jumpTwo3 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 1.0f, Vector2D(200.f, 18.f));
	Sprite* jumpTwo4 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(300.f, 18.f));
	Sprite* jumpTwo5 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(400.f, 27.f));
	Sprite* jumpTwo6 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(500.f, 30.f));
	Sprite* jumpTwo7 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(600.f, 30.f));
	Sprite* jumpTwo8 = new Sprite(PLAYER_TWO_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 10.0f, Vector2D(700.f, 30.f));

	std::vector<Sprite*> jumpTwo;

	jumpTwo.push_back(jumpTwo1);
	jumpTwo.push_back(jumpTwo2);
	jumpTwo.push_back(jumpTwo3);
	jumpTwo.push_back(jumpTwo4);
	jumpTwo.push_back(jumpTwo5);
	jumpTwo.push_back(jumpTwo6);
	jumpTwo.push_back(jumpTwo7);
	jumpTwo.push_back(jumpTwo8);

	AnimationClip* jumpTwoAnim = new AnimationClip(jumpTwo);
	mAllAnimationClips.emplace("PLAYER_TWO_JUMP", jumpTwoAnim);
#pragma endregion

#pragma region Die
	Sprite* dieTwo1 = new Sprite(PLAYER_TWO_DIE, Vector2D(0.5f, 0.5f), { 100, 125 }, 10.f, Vector2D(0.f, 30.f));

	std::vector<Sprite*> dieTwo;

	dieTwo.push_back(dieTwo1);

	AnimationClip* dieTwoAnim = new AnimationClip(dieTwo);
	mAllAnimationClips.emplace("PLAYER_TWO_DIE", dieTwoAnim);
#pragma endregion
#pragma endregion

#pragma region 말랭이
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/1.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/1.png");
	// Jump Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Jump/1.png");
	// Die Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Die/1.png");

#pragma region Idle
	Sprite* idleThree1 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(0.f, 30.f));
	Sprite* idleThree2 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(100.f, 30.f));
	Sprite* idleThree3 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(200.f, 30.f));
	Sprite* idleThree4 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(300.f, 30.f));
	Sprite* idleThree5 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(400.f, 30.f));
	Sprite* idleThree6 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(500.f, 30.f));
	Sprite* idleThree7 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(600.f, 30.f));
	Sprite* idleThree8 = new Sprite(PLAYER_ONE_IDLE, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(700.f, 30.f));

	std::vector<Sprite*> idleThree;

	idleThree.push_back(idleThree1);
	idleThree.push_back(idleThree2);
	idleThree.push_back(idleThree3);
	idleThree.push_back(idleThree4);
	idleThree.push_back(idleThree5);
	idleThree.push_back(idleThree6);
	idleThree.push_back(idleThree7);
	idleThree.push_back(idleThree8);

	AnimationClip* idleThreeAnim = new AnimationClip(idleThree);
	mAllAnimationClips.emplace("PLAYER_ONE_IDLE", idleThreeAnim);
#pragma endregion

#pragma region Run
	Sprite* runThree1 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(0.f, 30.f));
	Sprite* runThree2 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(100.f, 30.f));
	Sprite* runThree3 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(200.f, 30.f));
	Sprite* runThree4 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(300.f, 30.f));
	Sprite* runThree5 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(400.f, 30.f));
	Sprite* runThree6 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(500.f, 30.f));
	Sprite* runThree7 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(600.f, 30.f));
	Sprite* runThree8 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(700.f, 30.f));
	Sprite* runThree9 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(800.f, 30.f));
	Sprite* runThree10 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(900.f, 30.f));
	Sprite* runThree11 = new Sprite(PLAYER_ONE_RUN, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(1000.f, 30.f));

	std::vector<Sprite*> runThree;

	runThree.push_back(runThree1);
	runThree.push_back(runThree2);
	runThree.push_back(runThree3);
	runThree.push_back(runThree4);
	runThree.push_back(runThree5);
	runThree.push_back(runThree6);
	runThree.push_back(runThree7);
	runThree.push_back(runThree8);
	runThree.push_back(runThree9);
	runThree.push_back(runThree10);
	runThree.push_back(runThree11);

	AnimationClip* runThreeAnim = new AnimationClip(runThree);
	mAllAnimationClips.emplace("PLAYER_ONE_RUN", runThreeAnim);
#pragma endregion

#pragma region Jump
	Sprite* jumpThree1 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(0.f, 30.f));
	Sprite* jumpThree2 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.1f, Vector2D(100.f, 23.f));
	Sprite* jumpThree3 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 1.0f, Vector2D(200.f, 18.f));
	Sprite* jumpThree4 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(300.f, 18.f));
	Sprite* jumpThree5 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(400.f, 27.f));
	Sprite* jumpThree6 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(500.f, 30.f));
	Sprite* jumpThree7 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 0.15f, Vector2D(600.f, 30.f));
	Sprite* jumpThree8 = new Sprite(PLAYER_ONE_JUMP, Vector2D(0.5f, 0.5f), { 100, 125 }, 10.0f, Vector2D(700.f, 30.f));

	std::vector<Sprite*> jumpThree;

	jumpThree.push_back(jumpThree1);
	jumpThree.push_back(jumpThree2);
	jumpThree.push_back(jumpThree3);
	jumpThree.push_back(jumpThree4);
	jumpThree.push_back(jumpThree5);
	jumpThree.push_back(jumpThree6);
	jumpThree.push_back(jumpThree7);
	jumpThree.push_back(jumpThree8);

	AnimationClip* jumpThreeAnim = new AnimationClip(jumpThree);
	mAllAnimationClips.emplace("PLAYER_ONE_JUMP", jumpThreeAnim);
#pragma endregion

#pragma region Die
	Sprite* dieThree1 = new Sprite(PLAYER_ONE_DIE, Vector2D(0.5f, 0.5f), { 100, 125 }, 10.f, Vector2D(0.f, 30.f));

	std::vector<Sprite*> dieThree;

	dieThree.push_back(dieThree1);

	AnimationClip* dieThreeAnim = new AnimationClip(dieThree);
	mAllAnimationClips.emplace("PLAYER_ONE_DIE", dieThreeAnim);
#pragma endregion
#pragma endregion

#pragma region Intro
	// Intro
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\logo.png");
	Sprite* logo = new Sprite(INTRO_LOGO, Vector2D(0.5f, 0.5f), {1040.f, 450.f}, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_LOGO", logo);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\Game start.png");
	Sprite* startbutton = new Sprite(INTRO_START, Vector2D(0.5f, 0.5f), { 479.f, 155.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_START", startbutton);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\Game start2.png");
	Sprite* startbutton2 = new Sprite(INTRO_START2, Vector2D(0.5f, 0.5f), { 479.f, 155.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_START2", startbutton2);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\info.png");
	Sprite* info = new Sprite(INTRO_INFO, Vector2D(0.5f, 0.5f), { 161.f, 154.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_INFO", info);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\Tutorial.png");
	Sprite* tuto = new Sprite(INTRO_TUTO, Vector2D(0.5f, 0.5f), { 479.f, 154.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_TUTO", tuto);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\exit.png");
	Sprite* exit = new Sprite(INTRO_EXIT, Vector2D(0.5f, 0.5f), { 81.f, 79.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_EXIT", exit);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/UI\\copyright.png");
	Sprite* copy = new Sprite(INTRO_COPY, Vector2D(0.5f, 0.5f), { 560.f, 47.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("INTRO_COPY", copy);

	Graphics::GetInstance().LoadSpriteSheet(L"Resources/Object\\Fade.png");
	Sprite* fade = new Sprite(FADE_INOUT, Vector2D(0.5f, 0.5f), { 3840.f, 2160.f}, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("FADE_INOUT", fade);
#pragma endregion

#pragma region Stage1
	// Stage 1
	// 테이블에 등록된 이미지 파일들을 로드합니다. 엔진 내부의 map 구조에 저장합니다.
	ImageJson imageJson;

	imageJson.DeserializeFromFile("Resources/Json\\ImageResourceTable.json");

	for (auto iter = imageJson.mImageList.begin(); iter != imageJson.mImageList.end(); iter++)
		Graphics::GetInstance().LoadSpriteSheet(iter->imageID, iter->path);

	imageJson.mImageList.clear();


	Graphics::GetInstance().LoadSpriteSheet(L"Resources/Object\\Stage1\\StageOne.png");
	Sprite* stageOne = new Sprite(STAGE_1_BACKGROUND, Vector2D(0.5f, 0.5f), { 3840, 2160 }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("STAGE_1_BACKGROUND", stageOne);

#pragma endregion

#pragma region WEIGHT_CHAGE
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Weight change\\3 to 2.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Weight change\\2 to 3.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Weight change\\2 to 1.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Weight change\\1 to 2.png");

	Sprite* threeToTwo1 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(0.f, 30.f));
	Sprite* threeToTwo2 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(140.f, 0.f));
	Sprite* threeToTwo3 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(280.f, 0.f));
	Sprite* threeToTwo4 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(420.f, 0.f));
	Sprite* threeToTwo5 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(560.f, 0.f));
	Sprite* threeToTwo6 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(700.f, 0.f));
	Sprite* threeToTwo7 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(840.f, 0.f));
	Sprite* threeToTwo8 = new Sprite(THREE_TO_TWO, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> threeToTwo;

	threeToTwo.push_back(threeToTwo1);
	threeToTwo.push_back(threeToTwo2);
	threeToTwo.push_back(threeToTwo3);
	threeToTwo.push_back(threeToTwo4);
	threeToTwo.push_back(threeToTwo5);
	threeToTwo.push_back(threeToTwo6);
	threeToTwo.push_back(threeToTwo7);
	threeToTwo.push_back(threeToTwo8);

	AnimationClip* threeToTwoAnim = new AnimationClip(threeToTwo);
	mAllAnimationClips.emplace("THREE_TO_TWO", threeToTwoAnim);

	Sprite* TwoToThree1 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(0.f, 30.f));
	Sprite* TwoToThree2 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(140.f, 0.f));
	Sprite* TwoToThree3 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(280.f, 0.f));
	Sprite* TwoToThree4 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(420.f, 0.f));
	Sprite* TwoToThree5 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(560.f, 0.f));
	Sprite* TwoToThree6 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(700.f, 0.f));
	Sprite* TwoToThree7 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(840.f, 0.f));
	Sprite* TwoToThree8 = new Sprite(TWO_TO_THREE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> TwoToThree;

	TwoToThree.push_back(TwoToThree1);
	TwoToThree.push_back(TwoToThree2);
	TwoToThree.push_back(TwoToThree3);
	TwoToThree.push_back(TwoToThree4);
	TwoToThree.push_back(TwoToThree5);
	TwoToThree.push_back(TwoToThree6);
	TwoToThree.push_back(TwoToThree7);
	TwoToThree.push_back(TwoToThree8);

	AnimationClip* TwoToThreeAnim = new AnimationClip(TwoToThree);
	mAllAnimationClips.emplace("TWO_TO_THREE", TwoToThreeAnim);

	Sprite* TwoToOne1 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(0.f, 30.f));
	Sprite* TwoToOne2 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(140.f, 0.f));
	Sprite* TwoToOne3 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(280.f, 0.f));
	Sprite* TwoToOne4 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(420.f, 0.f));
	Sprite* TwoToOne5 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(560.f, 0.f));
	Sprite* TwoToOne6 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(700.f, 0.f));
	Sprite* TwoToOne7 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(840.f, 0.f));
	Sprite* TwoToOne8 = new Sprite(TWO_TO_ONE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> TwoToOne;

	TwoToOne.push_back(TwoToOne1);
	TwoToOne.push_back(TwoToOne2);
	TwoToOne.push_back(TwoToOne3);
	TwoToOne.push_back(TwoToOne4);
	TwoToOne.push_back(TwoToOne5);
	TwoToOne.push_back(TwoToOne6);
	TwoToOne.push_back(TwoToOne7);
	TwoToOne.push_back(TwoToOne8);

	AnimationClip* TwoToOneAnim = new AnimationClip(TwoToOne);
	mAllAnimationClips.emplace("TWO_TO_ONE", TwoToOneAnim);

	Sprite* OneToTwo1 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(0.f, 30.f));
	Sprite* OneToTwo2 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(140.f, 0.f));
	Sprite* OneToTwo3 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(280.f, 0.f));
	Sprite* OneToTwo4 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(420.f, 0.f));
	Sprite* OneToTwo5 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(560.f, 0.f));
	Sprite* OneToTwo6 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(700.f, 0.f));
	Sprite* OneToTwo7 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.596f), { 140, 155 }, 0.3f, Vector2D(840.f, 0.f));
	Sprite* OneToTwo8 = new Sprite(ONE_TO_TWO, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.3f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> OneToTwo;

	OneToTwo.push_back(OneToTwo1);
	OneToTwo.push_back(OneToTwo2);
	OneToTwo.push_back(OneToTwo3);
	OneToTwo.push_back(OneToTwo4);
	OneToTwo.push_back(OneToTwo5);
	OneToTwo.push_back(OneToTwo6);
	OneToTwo.push_back(OneToTwo7);
	OneToTwo.push_back(OneToTwo8);

	AnimationClip* OneToTwoAnim = new AnimationClip(OneToTwo);
	mAllAnimationClips.emplace("ONE_TO_TWO", OneToTwoAnim);

#pragma endregion

#pragma region DIESCENE
	// DIESCENE - FACE
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\Game Over.png");
	Sprite* face = new Sprite(DIE_FACE, Vector2D(0.5f, 0.5f), { 1920.f, 1080.f}, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("DIE_FACE", face);

	// DIESCENE - FACE
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\Restart.png");
	Sprite* restart = new Sprite(DIE_RESTART, Vector2D(0.5f, 0.5f), { 160.f, 154.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("DIE_RESTART", restart);

	// DIESCENE - NUMBERS
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\number\\game over.png");
	Sprite* numbers0 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_ZERO", numbers0);
	Sprite* numbers1 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(44.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_ONE", numbers1);
	Sprite* numbers2 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(88.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_TWO", numbers2);
	Sprite* numbers3 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(132.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_THREE", numbers3);
	Sprite* numbers4 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(176.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_FOUR", numbers4);
	Sprite* numbers5 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(220.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_FIVE", numbers5);
	Sprite* numbers6 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(264.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_SIX", numbers6);
	Sprite* numbers7 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(308.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_SEVEN", numbers7);
	Sprite* numbers8 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(352.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_EIGHT", numbers8);
	Sprite* numbers9 = new Sprite(DIE_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(396.f, 0.f));
	mAllSprites.emplace("DIE_NUMBERS_NINE", numbers9);

#pragma endregion

#pragma region OPTION
	// OPTION_MENU
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\menu.png");
	Sprite* menu = new Sprite(OPTION_MENU, Vector2D(0.5f, 0.5f), { 799.f / CAMERA_ZOOM, 847.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_MENU", menu);

	// OPTION_BACK_PROGRESS_BAR
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\ProgressBack.png");
	Sprite* backProgressBar = new Sprite(OPTION_BACK_PROGRESS_BAR, Vector2D::Zero, { 225.f / CAMERA_ZOOM, 58.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_BACK_PROGRESS_BAR", backProgressBar);

	// OPTION_FRONT_PROGRESS_BAR
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\ProgressFront.png");
	Sprite* frontProgressBar = new Sprite(OPTION_FRONT_PROGRESS_BAR, Vector2D::Zero, { 225.f / CAMERA_ZOOM, 58.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_FRONT_PROGRESS_BAR", frontProgressBar);

	// OPTION_FRONT_PROGRESS_BAR
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\ProgressBar.png");
	Sprite* progressBar = new Sprite(OPTION_PROGRESS_BAR, Vector2D::Zero, { 225.f / CAMERA_ZOOM, 58.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_PROGRESS_BAR", progressBar);

	// OPTION_BGMText
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\BGMText.png");
	Sprite* bgmText = new Sprite(OPTION_BGMText, Vector2D(0.5f, 0.5f), { 62.f / CAMERA_ZOOM, 24.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_BGM_TEXT", bgmText);

	// OPTION_SFXText
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\SFXText.png");
	Sprite* sfxText = new Sprite(OPTION_SFXText, Vector2D(0.5f, 0.5f), { 62.f / CAMERA_ZOOM, 24.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_SFX_TEXT", sfxText);

	// OPTION_RESTART
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\M_re start.png");
	Sprite* restartt = new Sprite(OPTION_RESTART, Vector2D(0.5f, 0.5f), { 143.f / CAMERA_ZOOM, 45.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_RESTART", restartt);

	// OPTION_BACK
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\M_game back.png");
	Sprite* back = new Sprite(OPTION_BACK, Vector2D(0.5f, 0.5f), { 148.f / CAMERA_ZOOM, 45.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_BACK", back);

	// OPTION_INTRO
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\M_title.png");
	Sprite* introro = new Sprite(OPTION_TITLE, Vector2D(0.5f, 0.5f), { 144.f / CAMERA_ZOOM, 45.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_TITLE", introro);

	// OPTION_EXIT
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\M_exit.png");
	Sprite* exittt = new Sprite(OPTION_EXIT, Vector2D(0.5f, 0.5f), { 146.f / CAMERA_ZOOM, 45.f / CAMERA_ZOOM }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("OPTION_EXIT", exittt);
#pragma endregion

#pragma region BODYSCALE
	// 체중계 본체
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\Weight.png");
	Sprite* bodyScale = new Sprite(UI_BODYSCALE, Vector2D(0.5f, 0.5f), { 319.f, 154.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("UI_BODYSCALE", bodyScale);

	// 체중계 숫자
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\number\\Weight.png");
	Sprite* scaleNumber0 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 54.f, 88.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_ZERO", scaleNumber0);
	Sprite* scaleNumber1 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(52.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_ONE", scaleNumber1);
	Sprite* scaleNumber2 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(104.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_TWO", scaleNumber2);
	Sprite* scaleNumber3 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(156.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_THREE", scaleNumber3);
	Sprite* scaleNumber4 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(208.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_FOUR", scaleNumber4);
	Sprite* scaleNumber5 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(260.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_FIVE", scaleNumber5);
	Sprite* scaleNumber6 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(312.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_SIX", scaleNumber6);
	Sprite* scaleNumber7 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(364.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_SEVEN", scaleNumber7);
	Sprite* scaleNumber8 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(416.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_EIGHT", scaleNumber8);
	Sprite* scaleNumber9 = new Sprite(UI_SCALENUMBER, Vector2D(0.5f, 0.5f), { 52.f, 88.f }, 0.f, Vector2D(468.f, 0.f));
	mAllSprites.emplace("SCALE_NUMBERS_NINE", scaleNumber9);
#pragma endregion

#pragma region HAMBURGER
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/ff.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/ff.png");
	// Attack Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/attack/ff.png");
	// Die Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Die/ff.png");

	idle1 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(0.f, 30.f));
	idle2 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(140.f, 30.f));
	idle3 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(280.f, 30.f));
	idle4 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(420.f, 30.f));
	idle5 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(560.f, 30.f));
	idle6 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(700.f, 30.f));
	idle7 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(840.f, 30.f));
	idle8 = new Sprite(ENEMY_BURGER_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> bugidle;

	bugidle.push_back(idle1);
	bugidle.push_back(idle2);
	bugidle.push_back(idle3);
	bugidle.push_back(idle4);
	bugidle.push_back(idle5);
	bugidle.push_back(idle6);
	bugidle.push_back(idle7);
	bugidle.push_back(idle8);

	AnimationClip* buggerIdle = new AnimationClip(bugidle);

	mAllAnimationClips.emplace("ENEMY_BURGER_IDLE", buggerIdle);

	run1 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(0.f, 30.f));
	run2 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(140.f, 30.f));
	run3 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(280.f, 30.f));
	run4 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(420.f, 30.f));
	run5 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(560.f, 30.f));
	run6 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(700.f, 30.f));
	run7 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(840.f, 30.f));
	run8 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(980.f, 30.f));
	run9 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(1120.f, 30.f));
	run10 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(1260.f, 30.f));
	run11 = new Sprite(ENEMY_BURGER_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(1400.f, 30.f));

	std::vector<Sprite*> bugrun;

	bugrun.push_back(run1);
	bugrun.push_back(run2);
	bugrun.push_back(run3);
	bugrun.push_back(run4);
	bugrun.push_back(run5);
	bugrun.push_back(run6);
	bugrun.push_back(run7);
	bugrun.push_back(run8);
	bugrun.push_back(run9);
	bugrun.push_back(run10);
	bugrun.push_back(run11);

	AnimationClip* buggerRun = new AnimationClip(bugrun);

	mAllAnimationClips.emplace("ENEMY_BURGER_RUN", buggerRun);

	Sprite* attack1 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(0.f, 30.f));
	Sprite* attack2 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(140.f, 30.f));
	Sprite* attack3 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(280.f, 30.f));
	Sprite* attack4 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(420.f, 30.f));
	Sprite* attack5 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(560.f, 30.f));
	Sprite* attack6 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(700.f, 30.f));
	Sprite* attack7 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(840.f, 30.f));
	Sprite* attack8 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(980.f, 30.f));
	Sprite* attack9 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(1120.f, 30.f));
	Sprite* attack10 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(1260.f, 30.f));
	Sprite* attack11 = new Sprite(ENEMY_BURGER_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(1400.f, 30.f));

	std::vector<Sprite*> bugattack;

	bugattack.push_back(attack1);
	bugattack.push_back(attack2);
	bugattack.push_back(attack3);
	bugattack.push_back(attack4);
	bugattack.push_back(attack5);
	bugattack.push_back(attack6);
	bugattack.push_back(attack7);
	bugattack.push_back(attack8);
	bugattack.push_back(attack9);
	bugattack.push_back(attack10);
	bugattack.push_back(attack11);

	AnimationClip* buggerAttack = new AnimationClip(bugattack);

	mAllAnimationClips.emplace("ENEMY_BURGER_ATTACK", buggerAttack);

	die1 = new Sprite(ENEMY_BURGER_DIE, Vector2D(0.5f, 0.5f), { 139.f, 121.f }, 10.f, Vector2D(0.f, 27.f));

	std::vector<Sprite*> bugdie;

	bugdie.push_back(die1);

	AnimationClip* buggerDie = new AnimationClip(bugdie);

	mAllAnimationClips.emplace("ENEMY_BURGER_DIE", buggerDie);
#pragma endregion

#pragma region BIRD
	// 그레이 버드
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/bird.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/bird.png");

	idle1 = new Sprite(BIRD_GRAY_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 80.f}, 0.15f, Vector2D(0.f, 0.f));

	std::vector<Sprite*> idlebirdGray;

	idlebirdGray.push_back(idle1);

	AnimationClip* idleBirdGray = new AnimationClip(idlebirdGray);

	mAllAnimationClips.emplace("BIRD_GRAY_IDLE", idleBirdGray);

	run1 = new Sprite(BIRD_GRAY_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(0.f, 0.f));
	run2 = new Sprite(BIRD_GRAY_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(80.f, 0.f));
	run3 = new Sprite(BIRD_GRAY_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(160.f, 0.f));
	run4 = new Sprite(BIRD_GRAY_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(240.f, 0.f));
	run5 = new Sprite(BIRD_GRAY_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(320.f, 0.f));

	std::vector<Sprite*> runbirdGray;

	runbirdGray.push_back(run1);
	runbirdGray.push_back(run2);
	runbirdGray.push_back(run3);
	runbirdGray.push_back(run4);
	runbirdGray.push_back(run5);

	AnimationClip* runBirdGray = new AnimationClip(runbirdGray);

	mAllAnimationClips.emplace("BIRD_GRAY_RUN", runBirdGray);

	// 블랡 버드
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/bird2.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/bird2.png");

	idle1 = new Sprite(BIRD_BLACK_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(0.f, 0.f));

	std::vector<Sprite*> idlebirdBlack;

	idlebirdBlack.push_back(idle1);

	AnimationClip* idleBirdBlack = new AnimationClip(idlebirdBlack);

	mAllAnimationClips.emplace("BIRD_BLACK_IDLE", idleBirdBlack);

	run1 = new Sprite(BIRD_BLACK_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(0.f, 0.f));
	run2 = new Sprite(BIRD_BLACK_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(80.f, 0.f));
	run3 = new Sprite(BIRD_BLACK_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(160.f, 0.f));
	run4 = new Sprite(BIRD_BLACK_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(240.f, 0.f));
	run5 = new Sprite(BIRD_BLACK_RUN, Vector2D(0.5f, 0.5f), { 80.f, 80.f }, 0.15f, Vector2D(320.f, 0.f));

	std::vector<Sprite*> runbirdBlack;

	runbirdBlack.push_back(run1);
	runbirdBlack.push_back(run2);
	runbirdBlack.push_back(run3);
	runbirdBlack.push_back(run4);
	runbirdBlack.push_back(run5);

	AnimationClip* runBirdBlack = new AnimationClip(runbirdBlack);

	mAllAnimationClips.emplace("BIRD_BLACK_RUN", runBirdBlack);
#pragma endregion
	
#pragma region Stage2_Background
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/Object\\Stage2\\StageTwo.png");
	Sprite* stagetwo = new Sprite(STAGE_2_BACKGROUND, Vector2D(0.5f, 0.5f), { 3840, 2160 }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("STAGE_2_BACKGROUND", stagetwo);
#pragma endregion

#pragma region Nacho_Shuriken
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/Object\\Stage1\\nacho.png");

	Sprite* shuri1 = new Sprite(NACHO_SHURIKEN, Vector2D(0.5f, 0.5f), { 80.f, 77.f}, 0.1f, Vector2D(0.f, 0.f));
	Sprite* shuri2 = new Sprite(NACHO_SHURIKEN, Vector2D(0.5f, 0.5f), { 80.f, 77.f }, 0.1f, Vector2D(80.f, 0.f));
	Sprite* shuri3 = new Sprite(NACHO_SHURIKEN, Vector2D(0.5f, 0.5f), { 80.f, 77.f }, 0.1f, Vector2D(160.f, 0.f));
	Sprite* shuri4 = new Sprite(NACHO_SHURIKEN, Vector2D(0.5f, 0.5f), { 80.f, 77.f }, 0.1f, Vector2D(240.f, 0.f));

	std::vector<Sprite*> shuriAnim;

	shuriAnim.push_back(shuri1);
	shuriAnim.push_back(shuri2);
	shuriAnim.push_back(shuri3);
	shuriAnim.push_back(shuri4);

	AnimationClip* shuri = new AnimationClip(shuriAnim);

	mAllAnimationClips.emplace("NACHO_SHURIKEN", shuri);
#pragma endregion

#pragma region SANDBAG
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/sand.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/snad.png");
	// Attack Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/attack/snad.png");
	// Die Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Die/snad.png");

	idle1 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(0.f, 30.f));
	idle2 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(140.f, 30.f));
	idle3 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(280.f, 30.f));
	idle4 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(420.f, 30.f));
	idle5 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(560.f, 30.f));
	idle6 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(700.f, 30.f));
	idle7 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(840.f, 30.f));
	idle8 = new Sprite(ENEMY_SANDBAG_IDLE, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> sandidle;

	sandidle.push_back(idle1);
	sandidle.push_back(idle2);
	sandidle.push_back(idle3);
	sandidle.push_back(idle4);
	sandidle.push_back(idle5);
	sandidle.push_back(idle6);
	sandidle.push_back(idle7);
	sandidle.push_back(idle8);

	AnimationClip* sandIdle = new AnimationClip(sandidle);

	mAllAnimationClips.emplace("ENEMY_SANDBAG_IDLE", sandIdle);

	run1 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(0.f, 30.f));
	run2 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(140.f, 30.f));
	run3 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(280.f, 30.f));
	run4 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(420.f, 30.f));
	run5 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(560.f, 30.f));
	run6 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(700.f, 30.f));
	run7 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(840.f, 30.f));
	run8 = new Sprite(ENEMY_SANDBAG_RUN, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> sandrun;

	sandrun.push_back(run1);
	sandrun.push_back(run2);
	sandrun.push_back(run3);
	sandrun.push_back(run4);
	sandrun.push_back(run5);
	sandrun.push_back(run6);
	sandrun.push_back(run7);
	sandrun.push_back(run8);

	AnimationClip* sandRun = new AnimationClip(sandrun);

	mAllAnimationClips.emplace("ENEMY_SANDBAG_RUN", sandRun);

	attack1 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(0.f, 30.f));
	attack2 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(140.f, 30.f));
	attack3 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(280.f, 30.f));
	attack4 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(420.f, 30.f));
	attack5 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(560.f, 30.f));
	attack6 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(700.f, 30.f));
	attack7 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(840.f, 30.f));
	attack8 = new Sprite(ENEMY_SANDBAG_ATTACK, Vector2D(0.5f, 0.5f), { 140, 125 }, 0.15f, Vector2D(980.f, 30.f));

	std::vector<Sprite*> sandattack;

	sandattack.push_back(attack1);
	sandattack.push_back(attack2);
	sandattack.push_back(attack3);
	sandattack.push_back(attack4);
	sandattack.push_back(attack5);
	sandattack.push_back(attack6);
	sandattack.push_back(attack7);
	sandattack.push_back(attack8);

	AnimationClip* sandAttack = new AnimationClip(sandattack);

	mAllAnimationClips.emplace("ENEMY_SANDBAG_ATTACK", sandAttack);

	die1 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(0.f, 30.f));
	Sprite* die2 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(140.f, 30.f));
	Sprite* die3 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(280.f, 30.f));
	Sprite* die4 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(420.f, 30.f));
	Sprite* die5 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(560.f, 30.f));
	Sprite* die6 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(700.f, 30.f));
	Sprite* die7 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(840.f, 30.f));
	Sprite* die8 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(980.f, 30.f));
	Sprite* die9 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(1120.f, 30.f));
	Sprite* die10 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(1260.f, 30.f));
	Sprite* die11 = new Sprite(ENEMY_SANDBAG_DIE, Vector2D(0.5f, 0.5f), { 140, 125.f }, 0.15f, Vector2D(1400.f, 30.f));

	std::vector<Sprite*> sanddie;

	sanddie.push_back(die1);
	sanddie.push_back(die2);
	sanddie.push_back(die3);
	sanddie.push_back(die4);
	sanddie.push_back(die5);
	sanddie.push_back(die6);
	sanddie.push_back(die7);
	sanddie.push_back(die8);
	sanddie.push_back(die9);
	sanddie.push_back(die10);
	sanddie.push_back(die11);

	AnimationClip* sandDie = new AnimationClip(sanddie);

	mAllAnimationClips.emplace("ENEMY_SANDBAG_DIE", sandDie);

#pragma endregion

#pragma region DUM
	// Idle Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Idle/dum.png");
	// Run Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Run/dum.png");
	// Die Anim
	Graphics::GetInstance().LoadSpriteSheet(L"Resources/character/sprite/Die/dum.png");

	idle1 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(0.f, 0.f));
	idle2 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(120.f, 0.f));
	idle3 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(240.f, 0.f));
	idle4 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(360.f, 0.f));
	idle5 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(480.f, 0.f));
	idle6 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(600.f, 0.f));
	idle7 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(720.f, 0.f));
	idle8 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(840.f, 0.f));
	Sprite* idle9 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f, 86.f }, 0.15f, Vector2D(960.f, 0.f));
	Sprite* idle10 = new Sprite(ENEMY_DUM_IDLE, Vector2D(0.5f, 0.5f), { 120.f,  86.f }, 0.15f, Vector2D(1080.f, 0.f));

	std::vector<Sprite*> dumidle;

	dumidle.push_back(idle1);
	dumidle.push_back(idle2);
	dumidle.push_back(idle3);
	dumidle.push_back(idle4);
	dumidle.push_back(idle5);
	dumidle.push_back(idle6);
	dumidle.push_back(idle7);
	dumidle.push_back(idle8);
	dumidle.push_back(idle9);
	dumidle.push_back(idle10);

	AnimationClip* dumIdle = new AnimationClip(dumidle);

	mAllAnimationClips.emplace("ENEMY_DUM_IDLE", dumIdle);

	run1 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(0.f, 0.f));
	run2 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(120.f, 0.f));
	run3 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(240.f, 0.f));
	run4 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(360.f, 0.f));
	run5 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(480.f, 0.f));
	run6 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(600.f, 0.f));
	run7 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(720.f, 0.f));
	run8 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(840.f, 0.f));
	run9 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f}, 0.15f, Vector2D(960.f, 0.f));
	run10 = new Sprite(ENEMY_DUM_RUN, Vector2D(0.5f, 0.5f), { 120.f, 90.f }, 0.15f, Vector2D(1080.f, 0.f));

	std::vector<Sprite*> dumrun;

	dumrun.push_back(run1);
	dumrun.push_back(run2);
	dumrun.push_back(run3);
	dumrun.push_back(run4);
	dumrun.push_back(run5);
	dumrun.push_back(run6);
	dumrun.push_back(run7);
	dumrun.push_back(run8);
	dumrun.push_back(run9);
	dumrun.push_back(run10);

	AnimationClip* dumRun = new AnimationClip(dumrun);

	mAllAnimationClips.emplace("ENEMY_DUM_RUN", dumRun);

	die1 = new Sprite(ENEMY_DUM_DIE, Vector2D(0.5f, 0.5f), { 120.f, 130.f }, 0.15f, Vector2D(0.f, 0.f));
	die2 = new Sprite(ENEMY_DUM_DIE, Vector2D(0.5f, 0.5f), { 120.f, 130.f }, 0.15f, Vector2D(120.f, 0.f));
	die3 = new Sprite(ENEMY_DUM_DIE, Vector2D(0.5f, 0.5f), { 120.f, 130.f }, 0.15f, Vector2D(240.f, 0.f));
	die4 = new Sprite(ENEMY_DUM_DIE, Vector2D(0.5f, 0.5f), { 120.f, 130.f }, 0.15f, Vector2D(360.f, 0.f));
	die5 = new Sprite(ENEMY_DUM_DIE, Vector2D(0.5f, 0.5f), { 120.f, 130.f }, 0.15f, Vector2D(480.f, 0.f));

	std::vector<Sprite*> dumdie;

	dumdie.push_back(die1);
	dumdie.push_back(die2);
	dumdie.push_back(die3);
	dumdie.push_back(die4);
	dumdie.push_back(die5);

	AnimationClip* dumDie = new AnimationClip(dumdie);

	mAllAnimationClips.emplace("ENEMY_DUM_DIE", dumDie);
#pragma endregion

#pragma region TRAPCAT
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\setup\\neko.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\attack\\neko.png");

	Sprite* setup1 = new Sprite(TRAP_CAT_SETUP, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(0.f, 0.f));
	Sprite* setup2 = new Sprite(TRAP_CAT_SETUP, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(100.f, 0.f));
	Sprite* setup3 = new Sprite(TRAP_CAT_SETUP, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(200.f, 0.f));
	Sprite* setup4 = new Sprite(TRAP_CAT_SETUP, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(300.f, 0.f));

	attack1 = new Sprite(TRAP_CAT_ATTACK, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(0.f, 0.f));
	attack2 = new Sprite(TRAP_CAT_ATTACK, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(100.f, 0.f));
	attack3 = new Sprite(TRAP_CAT_ATTACK, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(200.f, 0.f));
	attack4 = new Sprite(TRAP_CAT_ATTACK, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(300.f, 0.f));
	attack5 = new Sprite(TRAP_CAT_ATTACK, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(400.f, 0.f));
	attack6 = new Sprite(TRAP_CAT_ATTACK, Vector2D(0.5f, 0.5f), { 100.f, 130.f }, 0.05f, Vector2D(500.f, 0.f));

	std::vector<Sprite*> neko;

	neko.push_back(setup1);
	neko.push_back(setup2);
	neko.push_back(setup3);
	neko.push_back(setup4);
	neko.push_back(attack1);
	neko.push_back(attack2);
	neko.push_back(attack3);
	neko.push_back(attack4);
	neko.push_back(attack5);
	neko.push_back(attack6);

	AnimationClip* attackanim = new AnimationClip(neko);

	mAllAnimationClips.emplace("TRAP_CAT", attackanim);
#pragma endregion

#pragma region Dumbell
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\Object\\Stage2\\dum1.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\Object\\Stage2\\dum2.png");

	Sprite* niddle1 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(0.f, 0.f));
	Sprite* niddle2 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(158.f, 0.f));
	Sprite* niddle3 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(316.f, 0.f));
	Sprite* niddle4 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(474.f, 0.f));
	Sprite* niddle5 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(632.f, 0.f));
	Sprite* niddle6 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(790.f, 0.f));
	Sprite* niddle7 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(948.f, 0.f));
	Sprite* niddle8 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(1106.f, 0.f));
	Sprite* niddle9 = new Sprite(TRAP_NIDDLE_DUM_DOWN, Vector2D(0.5f, 0.5f), { 158.f, 159.f }, 0.07f, Vector2D(1264.f, 0.f));

	std::vector<Sprite*> niddleDum;

	niddleDum.push_back(niddle1);
	niddleDum.push_back(niddle2);
	niddleDum.push_back(niddle3);
	niddleDum.push_back(niddle4);
	niddleDum.push_back(niddle5);
	niddleDum.push_back(niddle6);
	niddleDum.push_back(niddle7);
	niddleDum.push_back(niddle8);
	niddleDum.push_back(niddle9);

	AnimationClip* niddleDumAnim = new AnimationClip(niddleDum);

	mAllAnimationClips.emplace("TRAP_NIDDLE_DUM_DOWN", niddleDumAnim);

	niddle1 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f}, 0.07f, Vector2D(0.f, 0.f));
	niddle2 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(127.555f, 0.f));
	niddle3 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(255.11f, 0.f));
	niddle4 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(382.665f, 0.f));
	niddle5 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(510.22f, 0.f));
	niddle6 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(637.775f, 0.f));
	niddle7 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(765.33f, 0.f));
	niddle8 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(892.88f, 0.f));
	niddle9 = new Sprite(TRAP_DUM_DOWN, Vector2D(0.5f, 0.5f), { 127.555f, 126.f }, 0.07f, Vector2D(1020.435f, 0.f));

	std::vector<Sprite*> Dumdown;

	Dumdown.push_back(niddle1);
	Dumdown.push_back(niddle2);
	Dumdown.push_back(niddle3);
	Dumdown.push_back(niddle4);
	Dumdown.push_back(niddle5);
	Dumdown.push_back(niddle6);
	Dumdown.push_back(niddle7);
	Dumdown.push_back(niddle8);
	Dumdown.push_back(niddle9);

	AnimationClip* DumDownAnim = new AnimationClip(Dumdown);

	mAllAnimationClips.emplace("TRAP_DUM_DOWN", DumDownAnim);
#pragma endregion

#pragma region WATCH
	// Colon
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\Time.png");
	// Time Numbers
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\number\\life&time.png");

	Sprite* colon = new Sprite(WATCH_COLON, Vector2D(0.5f, 0.5f), { 16.f, 55.f }, 0.f, Vector2D(0.f, 0.f));

	mAllSprites.emplace("WATCH_COLON", colon);

	Sprite* timeNum0 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(0.f, 0.f));
	Sprite* timeNum1 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(44.f, 0.f));
	Sprite* timeNum2 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(88.f, 0.f));
	Sprite* timeNum3 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(132.f, 0.f));
	Sprite* timeNum4 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(176.f, 0.f));
	Sprite* timeNum5 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(220.f, 0.f));
	Sprite* timeNum6 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(264.f, 0.f));
	Sprite* timeNum7 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(308.f, 0.f));
	Sprite* timeNum8 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(352.f, 0.f));
	Sprite* timeNum9 = new Sprite(WATCH_NUMBERS, Vector2D(0.5f, 0.5f), { 44.f, 60.f }, 0.f, Vector2D(396.f, 0.f));

	mAllSprites.emplace("WATCH_TIME_ZERO", timeNum0);
	mAllSprites.emplace("WATCH_TIME_ONE", timeNum1);
	mAllSprites.emplace("WATCH_TIME_TWO", timeNum2);
	mAllSprites.emplace("WATCH_TIME_THREE", timeNum3);
	mAllSprites.emplace("WATCH_TIME_FOUR", timeNum4);
	mAllSprites.emplace("WATCH_TIME_FIVE", timeNum5);
	mAllSprites.emplace("WATCH_TIME_SIX", timeNum6);
	mAllSprites.emplace("WATCH_TIME_SEVEN", timeNum7);
	mAllSprites.emplace("WATCH_TIME_EIGHT", timeNum8);
	mAllSprites.emplace("WATCH_TIME_NINE", timeNum9);

#pragma endregion

#pragma region Stage3_Background
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\Object\\stage3\\StageThree.png");

	Sprite* stage3 = new Sprite(STAGE_3_BACKGROUND, Vector2D(0.5f, 0.5f), { 3840.f, 2160.f }, 0.f, Vector2D(0.f, 0.f));

	mAllSprites.emplace("STAGE_3_BACKGROUND", stage3);

#pragma endregion

#pragma region ENEMY_FACE
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Idle\\ego.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Run\\ego.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Die\\ego.png");

	idle1 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(0.f, 0.f));
	idle2 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(80.f, 0.f));
	idle3 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(160.f, 0.f));
	idle4 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(240.f, 0.f));
	idle5 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(320.f, 0.f));
	idle6 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(400.f, 0.f));
	idle7 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(480.f, 0.f));
	idle8 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(560.f, 0.f));
	idle9 = new Sprite(ENEMY_FACE_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(640.f, 0.f));

	std::vector<Sprite*> faceidle;

	faceidle.push_back(idle1);
	faceidle.push_back(idle2);
	faceidle.push_back(idle3);
	faceidle.push_back(idle4);
	faceidle.push_back(idle5);
	faceidle.push_back(idle6);
	faceidle.push_back(idle7);
	faceidle.push_back(idle8);
	faceidle.push_back(idle9);

	AnimationClip* faceIdle = new AnimationClip(faceidle);

	mAllAnimationClips.emplace("ENEMY_FACE_IDLE", faceIdle);

	run1 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(0.f, 0.f));
	run2 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(80.f, 0.f));
	run3 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(160.f, 0.f));
	run4 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(240.f, 0.f));
	run5 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(320.f, 0.f));
	run6 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(400.f, 0.f));
	run7 = new Sprite(ENEMY_FACE_RUN, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.15f, Vector2D(480.f, 0.f));

	std::vector<Sprite*> facerun;

	facerun.push_back(run1);
	facerun.push_back(run2);
	facerun.push_back(run3);
	facerun.push_back(run4);
	facerun.push_back(run5);
	facerun.push_back(run6);
	facerun.push_back(run7);

	AnimationClip* faceRun = new AnimationClip(facerun);

	mAllAnimationClips.emplace("ENEMY_FACE_RUN", faceRun);

	die1 = new Sprite(ENEMY_FACE_DIE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.3f, Vector2D(0.f, 0.f));
	die2 = new Sprite(ENEMY_FACE_DIE, Vector2D(0.5f, 0.5f), { 80.f, 84.f }, 0.3f, Vector2D(80.f, 0.f));

	std::vector<Sprite*> facedie;

	facedie.push_back(die1);
	facedie.push_back(die2);

	AnimationClip* faceDie = new AnimationClip(facedie);

	mAllAnimationClips.emplace("ENEMY_FACE_DIE", faceDie);
#pragma endregion

#pragma region ENEMY_FUR
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Idle\\fur.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Run\\fur.png");
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\character\\sprite\\Die\\fur.png");

	idle1 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(0.f, 0.f));
	idle2 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(80.f, 0.f));
	idle3 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(160.f, 0.f));
	idle4 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(240.f, 0.f));
	idle5 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(320.f, 0.f));
	idle6 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(400.f, 0.f));
	idle7 = new Sprite(ENEMY_FUR_IDLE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(480.f, 0.f));

	std::vector<Sprite*> furidle;

	furidle.push_back(idle1);
	furidle.push_back(idle2);
	furidle.push_back(idle3);
	furidle.push_back(idle4);
	furidle.push_back(idle5);
	furidle.push_back(idle6);
	furidle.push_back(idle7);

	AnimationClip* furIdle = new AnimationClip(furidle);

	mAllAnimationClips.emplace("ENEMY_FUR_IDLE", furIdle);

	run1 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(0.f, 0.f));
	run2 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(80.f, 0.f));
	run3 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(160.f, 0.f));
	run4 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(240.f, 0.f));
	run5 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(320.f, 0.f));
	run6 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(400.f, 0.f));
	run7 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(480.f, 0.f));
	run8 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(560.f, 0.f));
	run9 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(640.f, 0.f));
	run10 = new Sprite(ENEMY_FUR_RUN, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(720.f, 0.f));

	std::vector<Sprite*> furrun;

	furrun.push_back(run1);
	furrun.push_back(run2);
	furrun.push_back(run3);
	furrun.push_back(run4);
	furrun.push_back(run5);
	furrun.push_back(run6);
	furrun.push_back(run7);
	furrun.push_back(run8);
	furrun.push_back(run9);
	furrun.push_back(run10);

	AnimationClip* furRun = new AnimationClip(furrun);

	mAllAnimationClips.emplace("ENEMY_FUR_RUN", furRun);

	die1 = new Sprite(ENEMY_FUR_DIE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(0.f, 0.f));
	die2 = new Sprite(ENEMY_FUR_DIE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(80.f, 0.f));
	die3 = new Sprite(ENEMY_FUR_DIE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(160.f, 0.f));
	die4 = new Sprite(ENEMY_FUR_DIE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(240.f, 0.f));
	die5 = new Sprite(ENEMY_FUR_DIE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(320.f, 0.f));
	die6 = new Sprite(ENEMY_FUR_DIE, Vector2D(0.5f, 0.5f), { 80.f, 60.f }, 0.15f, Vector2D(400.f, 0.f));

	std::vector<Sprite*> furdie;

	furdie.push_back(die1);
	furdie.push_back(die2);
	furdie.push_back(die3);
	furdie.push_back(die4);
	furdie.push_back(die5);
	furdie.push_back(die6);

	AnimationClip* furDie = new AnimationClip(furdie);

	mAllAnimationClips.emplace("ENEMY_FUR_DIE", furDie);

	// InGame - Life face UI
	Graphics::GetInstance().LoadSpriteSheet(L"Resources\\UI\\Life.png");
	Sprite* lifeFace = new Sprite(LIFE_FACE, Vector2D(0.5f, 0.5f), { 160.f, 154.f }, 0.f, Vector2D(0.f, 0.f));
	mAllSprites.emplace("LIFE_FACE", lifeFace);
#pragma endregion
}