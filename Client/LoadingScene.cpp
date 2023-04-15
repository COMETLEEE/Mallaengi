#include "PreCompiledHeader.h"
#include "LoadingScene.h"

#include "LoadingSceneObject.h"
#include "SubCamera.h"

LoadingScene::LoadingScene(std::string nextSceneName):
	Scene(nextSceneName + "LoadingScene"),
	mLoadSceneName(nextSceneName)
{

}

LoadingScene::~LoadingScene()
{

}

void LoadingScene::BuildScene()
{
	AddGameObject(new SubCamera());

	GameObject* object = new LoadingSceneObject(mLoadSceneName);
	
	AddGameObject(object);
}