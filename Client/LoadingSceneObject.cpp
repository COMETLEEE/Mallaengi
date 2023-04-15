#include "PreCompiledHeader.h"
#include "LoadingSceneObject.h"

LoadingSceneObject::LoadingSceneObject(std::string nextSceneName):
	mNextSceneName(nextSceneName),
	mLoadTime(0.f)
{

}

LoadingSceneObject::~LoadingSceneObject()
{

}

void LoadingSceneObject::FixedUpdate()
{
	GameObject::FixedUpdate();


}

void LoadingSceneObject::Update()
{
	GameObject::Update();

	mLoadTime += Timer::GetInstance().GetDeltaTime() / 1000.f;

	if (mLoadTime >= GARA_LOADING_TIME)
		Game::GetInstance().ReserveLoadScene(mNextSceneName);
}