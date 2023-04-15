#include "PreCompiledHeader.h"
#include "LoadingTrigger.h"

LoadingTrigger::LoadingTrigger(const string& triggerSceneName)
	: mTriggerSceneName(triggerSceneName)
{
	mCollision = AddAABBCollision();
}

LoadingTrigger::~LoadingTrigger()
{
}

void LoadingTrigger::Update()
{
	//if (mCollision->GetIsCollision() == true)
	//{
	//	if (Input::GetInstance().GetKeyState(VK_UP) == KEYSTATE::DOWN)
	//		Game::GetInstance().ReserveLoadScene(mTriggerSceneName);
	//}
}